#include "son_tmp_excute_mission.h"
#include "../../hardware/mcu/uart.h"
#include "../../hardware/mcu/timer.h"
#include "../../core/logging/son_tmp_piclog.h"

#include "son_tmp_mode_mission.h"
#include "son_tmp_mode_flash.h"

// ============================================================================
// グローバル変数の実体定義
// ============================================================================
unsigned int8 status = 0;
int1 is_use_smf_req_in_mission = 0;

// ============================================================================
// 初期化・ディスパッチ処理
// ============================================================================

void cigs_system_init(void)
{
    fprintf(PC, "CIGS System Initialize Start\r\n");

    // 全体の割り込みを一旦無効にして初期化を安全に行う
    disable_interrupts(GLOBAL);

    // タイマー・通信モジュールの初期化
    setup_timer();
    setup_uart_to_boss();

    // システム変数の初期化
    status = 0;
    is_use_smf_req_in_mission = 0;

    // 起動ログを保存
    piclog_make(PICLOG_STARTUP, 0x00);

    fprintf(PC, "CIGS System Initialize Complete\r\n");
}

static void process_boss_command(uint8_t cmd)
{
    fprintf(PC, "Received Command: 0x%02X\r\n", cmd);

    switch (cmd)
    {
        case CMD_MISSION_START:
        {
            status = EXECUTING_MISSION;
            // TODO: mode_mission 側のミッション実行関数を呼び出す
            // execute_mission_sequence();
            break;
        }
        case CMD_SMF_PREPARE:
        {
            status = COPYING;
            // TODO: mode_flash 側のSMF転送準備処理を呼び出す
            break;
        }
        case REQ_SMF_COPY:
        {
            // TODO: mode_flash 側のデータ転送処理を呼び出す
            break;
        }
        case CMD_SMF_PERMIT:
        {
            // TODO: mode_flash 側の転送許可処理を呼び出す
            break;
        }
        case REQ_POWER_OFF:
        {
            // 電源OFF要求処理
            status = IDLE;
            break;
        }
        default:
        {
            fprintf(PC, "Unknown Command: 0x%02X\r\n", cmd);
            break;
        }
    }
}

void cigs_execute_mission_loop(void)
{
    // 受信バッファにデータがあるか確認
    if (boss_receive_buffer_size > 0)
    {
        // 最初の1バイトをコマンドとして解釈
        uint8_t cmd = boss_receive_buffer[0];

        // コマンド受信ログを記録 (0x10 は仮のコマンド受信イベントID)
        piclog_make(0x10, cmd);

        // コマンドに応じた処理へ分岐
        process_boss_command(cmd);

        // 処理完了後、バッファをクリアして次の受信に備える
        boss_receive_buffer_size = 0;
        memset((void*)boss_receive_buffer, 0, RECEIVE_BUFFER_MAX);
    }

    // ステータスに応じたバックグラウンド処理があればここに記述
    // if (status == EXECUTING_MISSION) { ... }
}

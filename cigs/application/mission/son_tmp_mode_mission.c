#include "son_tmp_mode_mission.h"
#include "../../core/measurement/son_tmp_strain.h"
#include "../../core/logging/son_tmp_piclog.h"
#include "son_tmp_excute_mission.h"

// ============================================================================
// ミッション実行シーケンス
// ============================================================================

void execute_mission_sequence(void)
{
    fprintf(PC, "--- Mission Sequence Start ---\r\n");

    // ミッション開始ログの記録 (イベントID: 0x11, パラメータ: 0x00 と仮定)
    piclog_make(0x11, 0x00);

    // アナログスイッチ(MAX4734EUB+)で選択可能なチャンネル (0〜3)
    uint8_t num_channels = 4;

    // サンプリングレート設定 (例として 0x01 を指定)
    uint8_t samplingRate = 0x01;

    // 現在の動作モード (例として通常計測モード: 0x01 を指定)
    uint8_t mode = 0x01;

    // 全チャンネルを順番に計測するシナリオ
    for (uint8_t ch = 0; ch < num_channels; ch++)
    {
        fprintf(PC, "Executing Channel: %u\r\n", ch);

        // iv.c 側の計測処理を呼び出し（内部で温度計測も連続して呼ばれる）
        execute_measurement(mode, ch, samplingRate);

        // チャンネル切り替え間のインターバル
        delay_ms(100);
    }

    // ミッション終了ログの記録 (イベントID: 0x12, パラメータ: 0x00 と仮定)
    piclog_make(0x12, 0x00);

    // ミッション完了後、ステータスをIDLEに戻す
    //status = IDLE;

    // TODO: 必要であればここでBOSSへ完了応答(RES_MISSION_DONE)を送信する処理を追加

    fprintf(PC, "--- Mission Sequence Complete ---\r\n");
}
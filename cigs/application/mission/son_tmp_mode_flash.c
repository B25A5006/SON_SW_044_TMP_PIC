#include "son_tmp_mode_flash.h"
#include "son_tmp_excute_mission.h"
#include "../../core/logging/son_tmp_piclog.h"
#include "../../core/storage/son_tmp_smf.h"

// ============================================================================
// SMF（CPLD経由）転送シーケンス
// ============================================================================

void prepare_smf_transfer(void)
{
    fprintf(PC, "--- SMF Transfer Prepare ---\r\n");

    // 準備開始のログ記録 (イベントID: 0x20, パラメータ: 0x00 と仮定)
    piclog_make(0x20, 0x00);

    // 状態を COPYING に遷移 (excute_mission.c 側でも遷移済みだが念のため)
    //status = COPYING;

    // TODO: cigs_smf.c 側の転送準備処理（転送先頭アドレスの計算やキューの準備）を呼び出す
    // cigs_smf_prepare();
    cigs_smf_prepare();
}

void execute_smf_transfer(void)
{
    fprintf(PC, "--- SMF Transfer Execute ---\r\n");

    // 転送開始のログ記録 (イベントID: 0x21, パラメータ: 0x00 と仮定)
    piclog_make(0x21, 0x00);

    cigs_smf_copy();
}

void permit_smf_transfer(void)
{
    fprintf(PC, "--- SMF Transfer Permit ---\r\n");

    // 許可のログ記録 (イベントID: 0x22, パラメータ: 0x00 と仮定)
    piclog_make(0x22, 0x00);

    cigs_smf_permit();

    // 一連の転送シーケンスが完了したため、システム状態を IDLE に戻す
    status = IDLE;

    fprintf(PC, "--- SMF Transfer Sequence Complete ---\r\n");
}
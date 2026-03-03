#ifndef son_tmp_EXCUTE_MISSION_H
#define son_tmp_EXCUTE_MISSION_H

#include <stdint.h>
#include <stdbool.h>
#include "../../system/son_tmp_config.h"

/*
// ============================================================================
// ステータス定数定義
// （共通ヘッダ value_status.h に無い場合のフォールバック定義）
// ============================================================================
#ifndef IDLE
#define IDLE 0x00
#endif

#ifndef EXECUTING_MISSION
#define EXECUTING_MISSION 0x01
#endif

#ifndef COPYING
#define COPYING 0x02
#endif
*/

// ============================================================================
// グローバル変数
// ============================================================================
// uart.c などの割り込み処理内から参照されるシステム状態管理変数
//extern uint8_t status;
//extern bool is_use_smf_req_in_mission;

// ============================================================================
// 関数プロトタイプ
// ============================================================================
void cigs_system_init(void);
void cigs_excute_mission_loop(void);

#endif // son_tmp_EXCUTE_MISSION_H

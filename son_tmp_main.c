#include "cigs/system/son_tmp_main.h"  // ヘッダーファイルから自動的にインクルードされるため不要

void main()
{
    delay_ms(100); // wait for power stable
    fprintf(PC,"\r\n\r\n\r\n============================================================\r\n");
    fprintf(PC,"This is SHION TMP-PIC BBM1 Software\r\n");
    fprintf(PC,"Last updated on %s %s.\r\n\r\n", __DATE__, __TIME__);

    io_init();
    setup_uart_to_boss();
    setup_timer();
    misf_init();

    piclog_make(PICLOG_STARTUP,0x00);

    int1 is_finished = FALSE;
    fprintf(PC,"____TMP PIC Start Operation_____\r\n\r\n");


    fprintf(PC,"waiting for BOSS PIC command");

    //Start loop
    while(!is_finished)
    {
        if(boss_receive_buffer_size > 0)
        {
            //Command command = make_command(boss_receive_buffer, boss_receive_buffer_size);
            volatile Command recieve_cmd = make_receive_command(boss_receive_buffer, boss_receive_buffer_size);
            /*
            fprintf(PC, "Frame ID: %X\r\n", recieve_cmd.frame_id);
            fprintf(PC, "Content size: %u\r\n", recieve_cmd.size);
            fprintf(PC, "payload: ");
            for(int8 i = 0; i < recieve_cmd.size; i++)
                fprintf(PC, "%X ", recieve_cmd.content[i]);
            fprintf(PC, "\r\n\r\n");
            fprintf(PC, "is_exist: %d\r\n", recieve_cmd.is_exist);
            */
            clear_receive_signal(boss_receive_buffer, &boss_receive_buffer_size);

            if(recieve_cmd.is_exist)
                cigs_execute_mission_loop();
                fprintf(PC,"\r\nwaiting for BOSS PIC command");
        }

    // check `is break while loop`
        if(is_finished == TRUE)
            break;

        delay_ms(400);
        fprintf(PC, ".");
    }


    fprintf(PC, "\r\n\r\n======\r\n\r\nFinished process.\r\nWait for BOSS PIC turn off me");

    while (TRUE)
    {
        fprintf(PC, ".");
        delay_ms(1000);
    }

    fprintf(PC, "End main\r\n");

}
// Enf of files

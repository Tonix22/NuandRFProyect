/*
 * This file is part of the bladeRF project
 *
 * Copyright (C) 2013 Nuand LLC
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "input.h"
#include "input_impl.h"
#include "cmd.h"
#include "script.h"
#include "rel_assert.h"

#define COMMAND_DELIMITER ';'

static void exit_script(struct cli_state *s)
{
    int status;

    if (cli_script_loaded(s->scripts)) {

        status = cli_close_script(&s->scripts);
        if (status < 0) {
            cli_err(s, "Error", "Failed to close script.\n");
        }

        if (!cli_script_loaded(s->scripts)) {
            status = input_set_input(stdin);

            /* At least attempt to report something... */
            if (status < 0) {
                cli_err(s, "Error",
                        "Failed to reset terminal when exiting script.\n");
            }
        }
    }
}

/* Terminate the current command, as denoted by any delmiters,  with a '\0' and
 * return a pointer to the next command.
 *
 * Returns NULL if the end of the line was hit */
static inline char * zeroize_next_delimiter(char *line)
{
    size_t len, i;
    char * next_cmd = NULL;
    bool got_delimeter = false;
    bool in_quote = false;

    assert(line != NULL);

    len = strlen(line);

    for (i = 0; i < len && got_delimeter == false; i++) {
        switch(line[i]) {
            case '"':
                in_quote = !in_quote;
                break;

            case COMMAND_DELIMITER:
                if (in_quote == false) {
                    got_delimeter = true;
                    line[i] = '\0';

                    /* Is there more after this delimiter? */
                    if ((i + 1) < len) {
                        next_cmd = &line[i + 1];
                    }
                    break;
                }

            default:
                /* Skip past any other character */
                break;
        }
    }

    /* We don't need to worry about the state of in_quote before returning,
     * as the next stage of command execution will check for and report
     * unterminated quotes. */

    return next_cmd;
}

int input_loop(struct cli_state *s, bool interactive)
{
    char command[110];
    int status;
    const char *error;
    int counter = 0;
    char quit;

    status = input_init();

    status = 0;
    
    while (!cli_fatal(status) && status != CLI_RET_QUIT) {

        /* Give priority to commands issued via the '-e' cmdline option */
            
        //line = input_get_line(CLI_DEFAULT_PROMPT);
        
        memset(command,0,sizeof(command));
        counter++;
        switch (counter)
        {
        case 1:
            //strcpy(command,"tx config file=/home/tonix/Documents/CINVESTAV/setp-dic_2020/bladeRF/raw.csv format=csv");
            break;
        case 2:
            //strcpy(command,"tx config repeat=0 delay=1000");
            break;
        case 3:
            strcpy(command,"tx start");
            break;
        default:
            sleep(2);
            printf("\r\n");
            printf("press any key to end");
            system ("/bin/stty raw");
            quit = getc(stdin);
            strcpy(command,"exit");
            system ("/bin/stty cooked");
            printf("\r\n");
            break;
        }

        char *next_cmd = command;
        char *cmd;
        bool stop_execing_line = false;

        do {
            cmd = next_cmd;
            next_cmd = zeroize_next_delimiter(cmd);

            status = cmd_handle(s, cmd);

            if (status < 0) {
                /* Unlike a shell, we'll stop processing at the first
                    * command in a line that returned an error, as
                    * this is generally most appropriate. For example:
                    *   rx config ffile=samples.bin n=1M; rx start; rx wait 5s;
                    *
                    * Here it wouldn't make sense to try to execute 'rx start'
                    * if since the rx config was bogus.
                    */
                stop_execing_line = true;

                error = cli_strerror(status, s->last_lib_error);
                if (error) {
                    cli_err(s, "Error", "%s\n", error);
                }

                /* Stop executing script or command list */
                if (s->exec_from_cmdline) {
                    str_queue_clear(s->exec_list);
                } else {
                    exit_script(s);
                }

                /* Quit if we're not supposed to drop to a prompt */
                if (!interactive) {
                    status = CLI_RET_QUIT;
                }

            } else if (status > 0){
                switch (status) {
                    case CLI_RET_CLEAR_TERM:
                        input_clear_terminal();
                        break;
                    case CLI_RET_RUN_SCRIPT:
                        status = input_set_input(
                                cli_script_file(s->scripts));
                        if (status < 0) {
                            cli_err(s, "Error",
                                    "Failed to begin executing script\n");
                        }
                        break;
                    default:
                        cli_err(s, "Error", "Unknown return code: %d\n",
                                status);
                }
            }
        } while (next_cmd != NULL && stop_execing_line == false);

        /* Keep track our our script line count so we can report where
            * an error occurred. */
        cli_script_bump_line_count(s->scripts);
    }

    input_deinit();

    return 0;
}
/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <string.h>
#include <Application.h>
#include <ctype.h>
#include "TkShell.h"
#include <Codec.h>
#include <VolumeControl.h>
#include <pcm1770.h>
#include <Calibration.h>
#include <LED.h>

#define TK_SHELL_METHOD(c, verb)              int __tk_shell_ ## c ## _ ## verb(int __unused argc, char __unused **argv)
#define TK_SHELL_COMMAND(name, desc)          {#name, (tk_shell_command_verb_s *)__tk_shell_verbs_ ## name, desc}
#define TK_SHELL_VERBS(name)                  const tk_shell_command_verb_s __tk_shell_verbs_ ## name[] 
#define TK_SHELL_VERB(c, name, desc)          {#name, __tk_shell_ ## c ## _ ## name, desc}

#define CMD_BUF_LEN 64
#define TK_SHELL_MAX_ARGS 10

typedef struct
{
  const char *name;
  int        (*func)(int argc, char **argv);
  const char *desc;
} tk_shell_command_verb_s;

typedef struct
{
  const char *name;
  tk_shell_command_verb_s *verbs;
  const char *desc;
} tk_shell_command_s;


static const uint32_t reg_lookup[] = 
{
    CYREG_PRT0_DR,  // 0
    CYREG_PRT1_DR,  // 1
    CYREG_PRT2_DR,  // 2
    CYREG_PRT3_DR,  // 3
    CYREG_PRT4_DR,  // 4
    CYREG_PRT5_DR,  // 5
    CYREG_PRT6_DR,  // 6
    CYREG_PRT7_DR,  // 7
    CYREG_PRT8_DR,  // 8
    CYREG_PRT9_DR,  // 9
    CYREG_PRT10_DR, // 10
    CYREG_PRT11_DR, // 11
    CYREG_PRT12_DR, // 12
    CYREG_PRT13_DR, // 13
};
TK_SHELL_METHOD(gpio, set);
TK_SHELL_METHOD(gpio, config);
TK_SHELL_METHOD(gpio, get);
static TK_SHELL_VERBS(gpio) =
{
    TK_SHELL_VERB(gpio, set, "set GPIO state"),
    TK_SHELL_VERB(gpio, config, "configure GPIO"),
    TK_SHELL_VERB(gpio, get, "get GPIO state"),
    { "", NULL, "" }
};

TK_SHELL_METHOD(wm, vol_set);
TK_SHELL_METHOD(wm, vol_get);
TK_SHELL_METHOD(wm, reg_wr);
TK_SHELL_METHOD(wm, reg_rd);
static TK_SHELL_VERBS(wm) =
{
    TK_SHELL_VERB(wm, vol_set, "set volume level <vol:uint8>"),
    TK_SHELL_VERB(wm, vol_get, "get volume level"),
    TK_SHELL_VERB(wm, reg_wr, "write register <reg:uint8,data:uint16>)"),
    TK_SHELL_VERB(wm, reg_rd, "read register <reg:uint8>"),
    { "", NULL, "" }
};

TK_SHELL_METHOD(pcm, reg);
static TK_SHELL_VERBS(pcm) = 
{
    TK_SHELL_VERB(pcm, reg, "register read (rd) and write (wr) <reg:uint8,data:uint8>"),
    { "", NULL, "" }
};

TK_SHELL_METHOD(sys, crash);
TK_SHELL_METHOD(sys, info);
TK_SHELL_METHOD(sys, reset);
TK_SHELL_METHOD(sys, adc);
static TK_SHELL_VERBS(sys) = 
{
    TK_SHELL_VERB(sys, crash, "trigger a hard fault"),
    TK_SHELL_VERB(sys, info, "print info"),
    TK_SHELL_VERB(sys, reset, "trigger a SW reset"),
    TK_SHELL_VERB(sys, adc, "print ADC values"),
    { "", NULL, "" }
};

TK_SHELL_METHOD(led, pwm_period);
TK_SHELL_METHOD(led, start);
TK_SHELL_METHOD(led, stop);
static TK_SHELL_VERBS(led) =
{
    TK_SHELL_VERB(led, pwm_period, "set LED PWM period"),
    TK_SHELL_VERB(led, start, "start LED animation"),
    TK_SHELL_VERB(led, stop, "stop LED animation"),
    { "", NULL, "" }
};

TK_SHELL_METHOD(cal, print);
TK_SHELL_METHOD(cal, set);
TK_SHELL_METHOD(cal, save);
static TK_SHELL_VERBS(cal) =
{
    TK_SHELL_VERB(cal, print, "print cal data"),
    TK_SHELL_VERB(cal, set, "set cal data"),
    TK_SHELL_VERB(cal, save, "commit cal data to flash"),
    { "", NULL, "" }
};

static const tk_shell_command_s commands[] = 
{
    TK_SHELL_COMMAND(gpio, "GPIO commands"),
    TK_SHELL_COMMAND(wm, "Wolfson Codec commands"),
    TK_SHELL_COMMAND(pcm, "Burr-Brown Codec commands"),
    TK_SHELL_COMMAND(sys, "System commands"),
    TK_SHELL_COMMAND(led, "LED commands"),
    TK_SHELL_COMMAND(cal, "Calibration data commands"),
    { "", NULL, "" }
};

static char cmd_buf[CMD_BUF_LEN];
static uint8_t cmd_char_count;

////////////////////////////////////////////////////////////////////////////////
int strcicmp(char const *a, char const *b)
{
    for (;; a++, b++)
    {
        int d = tolower(*a) - tolower(*b);
        if (d != 0 || !*a)
            return d;
    }
}

TK_SHELL_METHOD(gpio, set)
{
    uint32_t port, pin, state;
    int i = 2;
    
    argc -= i;

    if (argc != 3)
    {
        PRINTF("Invalid number of arguments!\n");
        return -1;
    }
    
    port = atoi(argv[i++]);
    pin = atoi(argv[i++]);
    state = atoi(argv[i]);
    
    CY_SYS_PINS_SET_DRIVE_MODE(reg_lookup[port], pin, CY_SYS_PINS_DM_STRONG);

    if (state)
    {
        CY_SYS_PINS_SET_PIN(reg_lookup[port], pin);
    }
    else
    {
        CY_SYS_PINS_CLEAR_PIN(reg_lookup[port], pin);
    }
    
    PRINTF("> gpio:ok %d\n", (int)CY_SYS_PINS_READ_PIN(reg_lookup[port], pin));
    return 0;
}

TK_SHELL_METHOD(gpio, config)
{
    uint32_t port, pin, mode;
    int i = 2;
    
    argc -= i;

    if (argc != 3)
    {
        PRINTF("Invalid number of arguments!\n");
        return -1;
    }
    
    port = atoi(argv[i++]);
    pin = atoi(argv[i++]);
    mode = atoi(argv[i]);
    
    CY_SYS_PINS_SET_DRIVE_MODE(reg_lookup[port], pin, mode);
    
    return 0;
}

TK_SHELL_METHOD(gpio, get)
{
    uint32_t port, pin;
    int i = 2;
    
    argc -= i;

    if (argc != 2)
    {
        PRINTF("Invalid number of arguments!\n");
        return -1;
    }
    
    port = atoi(argv[i++]);
    pin = atoi(argv[i]);
    
    PRINTF("> gpio:ok %d\n", (int)CY_SYS_PINS_READ_PIN(reg_lookup[port], pin));
    
    return 0;
}

TK_SHELL_METHOD(wm, vol_set)
{
    int vol;
    int i = 2;
    uint8_t rv;
    
    argc -= i;
    
    if (argc != 1)
    {
        PRINTF("Invalid number of arguments!\n");
        return -1;
    }

    vol = atoi(argv[i++]);

    if ((rv = Codec_AdjustBothHeadphoneVolume(vol)) == 0)
    {
        PRINTF("> wm:ok\n");
    }
    else
    {
        PRINTF("> wm:er %d\n", rv);
        return -2;
    }

    return 0;
}

TK_SHELL_METHOD(wm, vol_get)
{
    PRINTF("> wm:ok %d\n", (int)Codec_GetHeadphoneVolume());

    return 0;
}

TK_SHELL_METHOD(wm, reg_wr)
{
    int i = 2;
    uint8_t reg;
    uint16_t data;
    int rv;
    
    argc -= i;
    
    if (argc != 2)
    {
        PRINTF("Invalid number of arguments!\n");
        return -1;
    }
    
    reg = atoi(argv[i++]);
    data = strtoul(argv[i++], NULL, 16);
    
    if ((rv = Codec_SendData(reg, data)) == 0)
    {
        PRINTF("> wm:ok\n");
    }
    else
    {
        PRINTF("> wm:er %d\n", rv);
        return -2;
    }
    
    return 0;
}

TK_SHELL_METHOD(wm, reg_rd)
{
    int i = 2;
    uint8_t reg;
    
    argc -= i;
    
    if (argc != 1)
    {
        PRINTF("Invalid number of arguments!\n");
        return -1;
    }
    
    reg = atoi(argv[i++]);
    
    PRINTF("> wm:ok 0x%04X\n", Codec_GetData(reg));
    
    return 0;
}

TK_SHELL_METHOD(pcm, reg)
{
    int i = 2;
    uint8 reg;
    uint8 data;
    
    argc -= i;
    
    if (argc != 3)
    {
        PRINTF("Invalid number of arguments!\n");
        return -1;
    }
    
    reg = atoi(argv[i + 1]);
    data = strtoul(argv[i + 2], NULL, 16);

    if (strcicmp(argv[i], "wr") == 0)
    {
        pcm1770_reg_write(reg, data);
    }
    
    PRINTF("> pcm:ok 0x%02X\n", pcm1770_reg_read(reg));
    
    return 0;
}

TK_SHELL_METHOD(sys, crash)
{
    void (*fp)(void) = NULL;
    
    fp();
    
    PRINTF("> sys:er\n");
    
    return 0;
}

TK_SHELL_METHOD(sys, info)
{
    PRINTF("> sys:ok %08lu\n", (unsigned long)sys_tick);

    return 0;
}

TK_SHELL_METHOD(sys, reset)
{
    CySoftwareReset();
    
    return 0;
}

TK_SHELL_METHOD(sys, adc)
{
    PRINTF("> sys:ok %d,%d\n", adcSample[vol_ctrl_left], adcSample[vol_ctrl_right]);
    
    return 0;
}

TK_SHELL_METHOD(led, pwm_period)
{
    int i = 2;
    
    argc -= i;
    
    if (argc != 1)
    {
        PRINTF("Invalid number of arguments!\n");
        return -1;
    }
    pwm_period = atoi(argv[2]);
    
    PRINTF("> led:ok\n");

    return 0;
}

TK_SHELL_METHOD(led, start)
{
    LedInit();
    
    PRINTF("> led:ok\n");

    return 0;
}

TK_SHELL_METHOD(led, stop)
{
    LedDeInit();
    
    PRINTF("> led:ok\n");

    return 0;
}

TK_SHELL_METHOD(cal, print)
{
    PRINTF("sign = 0x%08X\n", (unsigned int)cal_data->signature);
    PRINTF("ctr = %lu\n", cal_data->counter);
    PRINTF("adc_min[R] = %d\n", cal_data->adc_min[vol_ctrl_right]);
    PRINTF("adc_max[R] = %d\n", cal_data->adc_max[vol_ctrl_right]);
    PRINTF("adc_min[L] = %d\n", cal_data->adc_min[vol_ctrl_left]);
    PRINTF("adc_max[L] = %d\n", cal_data->adc_max[vol_ctrl_left]);

    PRINTF("led_max_brightness = %d\n", cal_data->led_max_brightness);
    PRINTF("debug_mask = 0x%02X\n", (unsigned int)cal_data->debug_mask);
    PRINTF("> cal:ok\n");

    return 0;    
}

TK_SHELL_METHOD(cal, set)
{
    int i = 2;
    
    argc -= i;
    
    if (argc == 0)
    {
        PRINTF("Invalid number of arguments!\n");
        return -1;
    }
    
    if (strcicmp(argv[i], "led_max_brightness") == 0)
    {
        cal_data->led_max_brightness = atoi(argv[++i]);
    }
    else if (strcicmp(argv[i], "adc_min_l") == 0)
    {
        cal_data->adc_min[vol_ctrl_left] = atoi(argv[++i]);
    }
    else if (strcicmp(argv[i], "debug_mask") == 0)
    {
        cal_data->debug_mask = strtoul(argv[++i], NULL, 16);
    }
    return 0;
}

TK_SHELL_METHOD(cal, save)
{
    PRINTF("> cal:ok %d\n", CalibrationSave());
    return 0;
}

static int TkShellProcessCommand(void)
{
    int retval = -1;
    char *buf = cmd_buf;
    bool found = false;
    char *argv[TK_SHELL_MAX_ARGS];
    int argc = 0;
    int i = 0, j = 0, k = 0;
    
    while (1)
    {
        // skip over whitespace
        while (*buf && isspace(*buf))
        {
          *buf = '\0';
          ++buf;
        }

        if (*buf == '\0')
        {
          break;
        }
        
        argv[argc] = buf;
        
        // skip over the rest of arg until whitespace again
        while (*buf && !isspace(*buf))
        {
            buf++;
        }
        ++argc;
        
        if (argc > TK_SHELL_MAX_ARGS)
        {
            PRINTF("Too many arguments!\n");
            return -2;
        }
    }
    
    if (argc > 0)
    {
        i = j = k = 0;
        while (strcmp(commands[i].name, "") != 0)
        {
            if (strcicmp(argv[0], commands[i].name) == 0)
            {
                while (strcmp(commands[i].verbs[j].name, "") != 0)
                {
                    if (strcicmp(argv[1], commands[i].verbs[j].name) == 0)
                    {
                        retval = commands[i].verbs[j].func(argc, argv);
                        found = true;
                        break;
                    }
                    else if (strcicmp(argv[1], "help") == 0)
                    {
                        found = true;
                        PRINTF("Displaying list of %s commands:\n", commands[i].name);
                        while (strcmp(commands[i].verbs[k].name, "") != 0)
                        {
                            PRINTF("\t%s %s: %s\n", commands[i].name, commands[i].verbs[k].name, commands[i].verbs[k].desc);
                            k++;
                        }
                        break;
                    }
                    j++;
                }

                if (found)
                {
                    break;
                }
            }
            else if (strcicmp(argv[0], "help") == 0)
            {
                found = true;
                PRINTF("Displaying list of commands:\n");
                while (strcmp(commands[j].name, "") != 0)
                {
                    PRINTF("\t%s: %s\n", commands[j].name, commands[j].desc);
                    j++;
                }
                break;
            }
            i++;
        }
    }
    
    if (!found)
    {
        PRINTF("unknown command: %s\n", argv[0]);
    }
    
    return retval;
}

void TkShellInit(void)
{
    memset((void *)cmd_buf, 0, CMD_BUF_LEN);
    cmd_char_count = 0;
}

void TkShellService(void)
{
    char c;

    while ((c = UART_UartGetChar()) != 0)
    {
        switch (c)
        {
            case '\r':
            case '\n':
            case 0x03:
                if (cmd_char_count > 0)
                {
                    PRINTF("\n");
                    TkShellProcessCommand();
                }
                PRINTF("\n\U00002744 ] ");
                cmd_char_count = 0;
                cmd_buf[0] = '\0';
                break;
                
            case 127:
            case '\b':
                if (cmd_char_count == 0)
                {
                    break;
                }
                cmd_buf[--cmd_char_count] = '\0';
                PRINTF("\b \b");
                break;

            default:
                PRINTF("%c", c);
                cmd_buf[cmd_char_count++] = c;
                cmd_buf[cmd_char_count] = '\0';
                break;
        }
    }
}
/* [] END OF FILE */

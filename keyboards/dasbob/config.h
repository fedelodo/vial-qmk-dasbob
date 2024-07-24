// Copyright 2024 Conor Burns (@Conor-Burns)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define EE_HANDS
/* Serial Config */
#define USE_SERIAL
#define SERIAL_USART_TX_PIN GP1
#define USB_VBUS_PIN GP19

#define TAPPING_TERM 200
#define PERMISSIVE_HOLD

#define AUDIO_PIN GP5
#define AUDIO_PWM_DRIVER PWMD2
#define AUDIO_PWM_CHANNEL RP2040_PWM_CHANNEL_B
#define AUDIO_INIT_DELAY
#define AUDIO_CLICKY
#define SENDSTRING_BELL
#define AUDIO_CLICKY_FREQ_RANDOMNESS 1.0f
#define TEMPO_DEFAULT 70
#define STARTUP_SONG SONG(NOKIA_TUNE)

#define STARTUP_SOUND E__NOTE(_E6), E__NOTE(_A6), ED_NOTE(_E7),

#define NOKIA_TUNE E__NOTE(_E6), E__NOTE(_D6), Q__NOTE(_FS5), Q__NOTE(_GS5), E__NOTE(_CS6), E__NOTE(_B5), Q__NOTE(_D5), Q__NOTE(_E5), E__NOTE(_B5), E__NOTE(_A5), Q__NOTE(_CS5), Q__NOTE(_E5), HD_NOTE(_A5),
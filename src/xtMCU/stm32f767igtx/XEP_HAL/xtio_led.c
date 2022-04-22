/**
  * @file
  * @date     2022-01-12
  * @author   yxnan <yxnan@pm.me>
  * @brief    Implementation of LED controls for custom boards with STM32F767 MCU
  *
  * See @ref XEP_HAL.h for more documentation.
  *
  * @todo Implement PWM mode for LEDs
*/

#include "xtio_led.h"
#include "board.h"
#include "gpio_wrapper.h"

DEF_GPIO(pin_led_red,   LED_R_GPIO_Port, LED_R_Pin);
DEF_GPIO(pin_led_green, LED_G_GPIO_Port, LED_G_Pin);
DEF_GPIO(pin_led_blue,  LED_B_GPIO_Port, LED_B_Pin);

static int xtio_decode_led_id(xtio_led_id_t led_id, gpio_pin **pin)
{
    switch (led_id)
    {
        case XTIO_LED_RED:
            *pin = &pin_led_red;
            break;
        case XTIO_LED_GREEN:
            *pin = &pin_led_green;
            break;
        case XTIO_LED_BLUE:
            *pin = &pin_led_blue;
            break;
        default:
            return XTIO_WRONG_LED_ID;
    }
    return XT_SUCCESS;
}

static GPIO_PinState from_led_state(float led_state)
{
    if (0.5 <= led_state)   // 输出低电平时导通
        return GPIO_PIN_RESET;
    else
        return GPIO_PIN_SET;
}

int xtio_led_init(
    xtio_led_id_t led_id,
    int mode,
    float led_state
)
{
    // GPIO 的初始化已在启动时完成
    UNUSED(mode);
    return xtio_led_set_state(led_id, led_state);
}

int xtio_led_set_state(
    xtio_led_id_t led_id,
    float led_state
)
{
    gpio_pin *pin = NULL;
    int status = xtio_decode_led_id(led_id, &pin);
    gpio_set(*pin, from_led_state(led_state));

    return status;
}

int xtio_led_toggle_state(
    xtio_led_id_t led_id
)
{
    gpio_pin *pin = NULL;
    int status = xtio_decode_led_id(led_id, &pin);
    gpio_toggle(*pin);

    return status;
}

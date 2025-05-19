#include <stm32g4xx_hal.h>
#include <stdbool.h>

HAL_StatusTypeDef SystemClock_Config(void);
void SysTick_Handler(void);
void halt(void);

int main(void) {
  HAL_StatusTypeDef err = HAL_OK;
  err = HAL_Init();
  if (err != HAL_OK) halt();
  err = SystemClock_Config();
  if (err != HAL_OK) halt();

  GPIO_InitTypeDef led = {
    .Mode = GPIO_MODE_OUTPUT_PP,
    .Pin = GPIO_PIN_5,
    .Pull = GPIO_PULLUP,
    .Speed = GPIO_SPEED_FREQ_HIGH,
  };

  GPIO_InitTypeDef button = {
    .Mode = GPIO_MODE_INPUT,
    .Pin = GPIO_PIN_13,
    .Pull = GPIO_PULLDOWN,
    .Speed = GPIO_SPEED_FREQ_HIGH,
  };

  HAL_GPIO_Init(GPIOA, &led);
  HAL_GPIO_Init(GPIOC, &button);

  GPIO_PinState state;

  while (true) {
    state = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
    if(state == GPIO_PIN_SET) continue;
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    HAL_Delay(500);
  }
}

HAL_StatusTypeDef SystemClock_Config(void) {
  HAL_StatusTypeDef err = HAL_OK;

  RCC_OscInitTypeDef RCC_OscInitStruct = {
    .OscillatorType = RCC_OSCILLATORTYPE_HSI,
    .HSIState = RCC_HSI_ON,
    .HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT,
    .PLL.PLLState = RCC_PLL_NONE,
  };
  err = HAL_RCC_OscConfig(&RCC_OscInitStruct);
  if (err != HAL_OK) return err;

  RCC_ClkInitTypeDef RCC_ClkInitStruct = {
    .ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                                  RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2,
    .SYSCLKSource = RCC_SYSCLKSOURCE_HSI,
    .AHBCLKDivider = RCC_SYSCLK_DIV1,
    .APB1CLKDivider = RCC_HCLK_DIV1,
  };
  err = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0);
  if (err != HAL_OK) return err;

  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  return HAL_OK;
}


void SysTick_Handler(void) {
  HAL_IncTick();
}

void halt(void) {
  while(0) {}
}
#include "tasks.h"

extern TIM_HandleTypeDef htim2;
extern IWDG_HandleTypeDef hiwdg;

volatile uint32_t tick = 0; // 全局计数器，供任务系统使用

// 定时器更新回调：仅在 TIM2 触发时更新计数，并刷新看门狗
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim == NULL) {
        return;
    }

    if (htim->Instance == TIM2) {
        tick++;
        HAL_IWDG_Refresh(&hiwdg);
    }
}

// 任务初始化：关闭 LED，并启动 TIM2 中断定时器
void Tasks_Init(void) {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
    HAL_TIM_Base_Start_IT(&htim2);
}
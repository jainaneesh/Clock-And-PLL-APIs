/*
 * msp.c
 *
 *  Created on: Dec 18, 2023
 *      Author: jaina
 */
#include "stm32f4xx_hal.h"

void HAL_MspInit(void)
{
	//Here we will do low level processor specific inits
	//1. Setup the priority grouping of the arm cortex mx processor
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
	//2. Enable the required system exceptions of the arm cortex mx processor
	SCB->SHCSR |= 0x7 << 16;
	//3. Configure the priority for the system exceptions
	HAL_NVIC_SetPriority(MemoryManagement_IRQn,0,0);
	HAL_NVIC_SetPriority(BusFault_IRQn,0,0);
	HAL_NVIC_SetPriority(UsageFault_IRQn,0,0);
}
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	//Creating a variable for GPIO InitTypeDef
	GPIO_InitTypeDef gpio_uart;
	//Here we are going to do the low level initialization of the UART2 peripheral
	//1. Enable clock for USART2 peripheral
	__HAL_RCC_USART2_CLK_ENABLE();
	//1.1 Enabling the clock for GPIO Port A
	__HAL_RCC_GPIOA_CLK_ENABLE();
	//2. Pin muxing configurations
	//Pin muxing for TX
	gpio_uart.Pin = GPIO_PIN_2;
	gpio_uart.Mode = GPIO_MODE_AF_PP;
	gpio_uart.Pull = GPIO_PULLUP;
	gpio_uart.Speed = GPIO_SPEED_FREQ_LOW;
	gpio_uart.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA,&gpio_uart);
	//Pin muxing for RX
	gpio_uart.Pin = GPIO_PIN_3;
	HAL_GPIO_Init(GPIOA,&gpio_uart);
	//3. Enable the IRQ and set up the priority (NVIC settings)
	HAL_NVIC_EnableIRQ(USART2_IRQn);
	HAL_NVIC_SetPriority(USART2_IRQn,15,0);
}

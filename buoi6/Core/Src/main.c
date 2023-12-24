
#include "main.h"
#include "usart.h"
#include "gpio.h"


#include <stdio.h>
#include <string.h>

#define MAX_DATA_SIZE 100
typedef enum bool{false,true}bool;
uint8_t receive;
char arr_receive[100];
bool en_write_arr=false ;
bool done_frame=false;
bool allow=true;
char count=0;
char mang[10];
uint8_t i=0;
uint8_t data[100];
uint8_t x, y;
char temp ;
int sophantu, newtemp;

void SystemClock_Config(void);

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart ->Instance ==huart2.Instance )
	{
		 if(en_write_arr == false ){
			 en_write_arr=true ;
			 done_frame=false;
			}
			if(en_write_arr==true){

							arr_receive[count]=receive;
							if(arr_receive[count]>='0'&arr_receive[count]<='9')	temp = temp*10 + (arr_receive[count]-48);
						
					if(arr_receive[count] ==' ') {
							data[sophantu]=temp;
							temp = 0 ;
							sophantu++;
						}	
					}
				for (x = 0; x < sophantu - 1 ; x++) {
					for (y = 0; y < sophantu - x -1 ; y++) {
						if (data[y] > data[y + 1]) {
							newtemp = data[y];
							data[y] = data[y + 1];
							data[y + 1] = newtemp;
						}
					}
				}	
					count++;
			
	 
			if(receive=='p' && en_write_arr == true){
						en_write_arr =false;
						done_frame = true;
						
				}
			HAL_UART_Receive_IT(&huart2 ,&receive ,1);
		}
}

int main(void)
{
 
  HAL_Init();

  SystemClock_Config();

 
  MX_GPIO_Init();
  MX_USART2_UART_Init();

	HAL_UART_Receive_IT(&huart2 ,&receive ,1);

  
  while (1)
  {
    
		
			if(done_frame == true){
				for(int z =0; z < sophantu ; z++){
					sprintf(mang,"\n %d",data[z]);
					HAL_UART_Transmit(&huart2,(uint8_t*)mang,strlen(mang),100);
				}
			memset(arr_receive, 0, 100);
			memset(data, 0, 100);
			count = 0;
			sophantu=0;
			done_frame = false;
			}
		
  }
 
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

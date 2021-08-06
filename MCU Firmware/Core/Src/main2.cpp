/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//Ben
#include "decisiontree.cpp"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <map>
#include <algorithm>
using namespace std;

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_rx;

//uint8_t buffer_rx[100];
char buffer_rx[100];

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

//Ben
vector<Table> recData(){
	//code to be added, default here
	Table t1;
	Table t2;
	Table t3;
	vector<Table> vec{t1,t2,t3};
	return vec;
}

/*void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
}*/

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){



}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */




  // More Jan Code ________________________


  int send (char * txData){
  //
  int bytesToSend =10+strlen(txData);
  char send[500];


  send[0]='#';

  //length of payload
  // Todo: maybe overflow an Bytes
  char msglen [11];
  sprintf(msglen,"%d",strlen(txData));

  int i =1;
  while (i<(strlen(msglen)+1)){
  send[i]=msglen[i-1];
  i=i+1;
  }
  send[i]='|';
  i=i+1;
  int sendi=0;
  while(sendi<strlen(txData)){
  send[i] = txData[sendi];
  i=i+1;
  sendi=sendi+1;
  }



  //Union length of payload and payload, send it
  //strcat (send, txData);
  HAL_UART_Transmit(&huart2, (uint8_t *)  send, strlen(send),400);
  return 1;

  }









  int receiev (char * txData){
  while (1){
	HAL_UART_Receive(&huart2,buffer_rx,1,1000);
	if (buffer_rx[0]== (uint8_t) '#')
		{
		break;
		}

	}

	//check for payload length
	int j=0;
	char msglen [8];
	while (1){
	HAL_UART_Receive(&huart2,buffer_rx,1,1000);
	if (buffer_rx[0]== (uint8_t) '|')
		{
		break;
		}
	msglen[j]=buffer_rx[0];
	j= j+1;
	}

	int msglength=0;
	sscanf (msglen, "%d", &msglength);

	//Check for unuseful |
	//HAL_UART_Receive(&huart2,buffer_rx,1,1000);

	//receive payload
	HAL_UART_Receive(&huart2,buffer_rx,msglength,1000);


	 int i =0;
	while (i<msglength){
	txData[i]=buffer_rx[i];
	buffer_rx[i]=NULL;
	i=i+1;
	}

  	return 1;
  }



  //Ben
  char * TableToString(Table t1){
	  string attrName = {};
	  string data = {};
	  string attrValueList = {};

	  int attrNameSize = t1.attrName.size();

	  for(int i = 0; i < attrNameSize; i++){
		  if(i==0){
			  attrName = t1.attrName[0];
		  }else{
			  attrName.append("#");
			  attrName.append(t1.attrName[i]);
		  }
	  }

	  for(int i = 0; i < t1.data.size(); i++){
		  for(int a = 0; a < t1.data[i].size();a++){
			  if(a == 0){
				  data.append(t1.data[i][a]);
			  }else{
				  data.append("#");
				  data.append(t1.data[i][a]);
			  }
		  }
		  if(i != t1.data.size()-1){
			  data.append("$");
		  }
	  }

	  for(int i = 0; i < t1.attrValueList.size(); i++){
	  		  for(int a = 0; a < t1.attrValueList[i].size();a++){
	  			  if(a == 0){
	  				  data.append(t1.attrValueList[i][a]);
	  			  }else{
	  				  data.append("#");
	  				  data.append(t1.attrValueList[i][a]);
	  			  }
	  		  }
	  		  if(i != t1.attrValueList.size()-1){
	  			  data.append("$");
	  		  }
	  	  }

	  string final = attrName;
	  final.append("/");
	  final.append(data);
	  final.append("/");
	  final.append(attrValueList);

	  char* c = const_cast<char*>(final.c_str());

	  return c;
  }


  void SplitStringH(string s, vector<string> &v){

  	string temp = "";
  	for(int i=0;i<s.length();++i){

  		if(s[i]=='#'){
  			v.push_back(temp);
  			temp = "";
  		}
  		else{
  			temp.push_back(s[i]);
  		}

  	}
  	v.push_back(temp);

  }

  void SplitStringD(string s, vector<string> &v){

    	string temp = "";
    	for(int i=0;i<s.length();++i){

    		if(s[i]=='$'){
    			v.push_back(temp);
    			temp = "";
    		}
    		else{
    			temp.push_back(s[i]);
    		}

    	}
    	v.push_back(temp);

    }

  void SplitStringS(string s, vector<string> &v){

    	string temp = "";
    	for(int i=0;i<s.length();++i){

    		if(s[i]=='/'){
    			v.push_back(temp);
    			temp = "";
    		}
    		else{
    			temp.push_back(s[i]);
    		}

    	}
    	v.push_back(temp);

    }

//interne trennung # - extern $
  Table StringToTable(char * s1){
	  vector<string> input;

	  //may be different depending on libraries
	  //string slashString = str(s1);
	  std::string slashString(s1);

	  SplitStringS(slashString,input);

	  string attrName = input[0];
	  string data = input[1];
	  string attrValueList = input[2];

	 vector<string> attrNamefinal;
	 SplitStringH(attrName,attrNamefinal);



	 vector<string> datafinal;
	 SplitStringD(data,datafinal);

	 vector<vector<string>> datafinalfinal;
	 for(int i = 0; i< datafinal.size();i++){
		 SplitStringH(datafinal[i],datafinalfinal[i]);
	 }



	 vector<string> attrValueListfinal;
	 	 SplitStringD(attrValueList,attrValueListfinal);

	 vector<vector<string>> attrValueListfinalfinal;
	 for(int i = 0; i< attrValueListfinal.size();i++){
	 	 SplitStringH(attrValueListfinal[i],attrValueListfinalfinal[i]);
	 }

	 Table tf;
	       tf.attrName=attrNamefinal;
	       tf.data=datafinalfinal;
	       tf.attrValueList=attrValueListfinalfinal;


	 return tf;
  }



int main(void)
{
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART2_UART_Init();

	/*
	//char txData[5000] ="Hello World Test\r\n ";
	char txData[5000] ="";
	char senda[5000] ="Hello World Test\r\n";

   Infinite loop

	while(1){
	// print a int to tXDATA
	//msglength=222;
	//sprintf(  txData,"%d",msglength);
	  receive(txData);
	  HAL_Delay(500);
		send(txData);
		HAL_Delay(500);
	}*/

  //Ben
  /* USER CODE BEGIN 2 */

      vector<string> attrName;
      vector<vector<string> > data;

      vector<vector<string> > attrValueList;

      //examples - need to be adjusted
      attrName = {"age","income","student","credit_rating","Class:buys_computer"};
      data = {{"<=30","high","no","fair","no"},
    		  {"<=30","high","no","excellent","no"},
    		  {"31...40","high","no","fair","yes"}};


      Table table;
      table.attrName=attrName;
      table.data=data;
      table.attrValueList=attrValueList;

      //initializing the DecisionTree
      DecisionTree decTree(table) ;


      //Observation table
      vector<string> obsattrName;
      vector<vector<string> > obsdata;

      vector<vector<string> > obsattrValueList;


      //example - needs to get filled with the data that is received
      obsattrName = {"age","income","student","credit_rating"};
      obsdata = {{"<=30","high","no","fair"},
        		   {"<=30","high","no","excellent"},
        		   {"31...40","high","no","fair"}};


      Table obstable;
      table.attrName=obsattrName;
      table.data=obsdata;
      table.attrValueList=obsattrValueList;


      Table res;


      //This bool will decide whether the drone is the master drone
      bool master = true;


    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1)
    {
      /* USER CODE END WHILE */

      /* USER CODE BEGIN 3 */

  	  //Classification

  	  for(int i=0;i < obstable.data.size(); i++) {
  	  		vector<string> result = obstable.data[i];
  	  		result.push_back(decTree.guess(obstable.data[i]));
  	  		res.data.push_back(result);
  	  	}

  	  //Send results of classification to master
  	  if(!master){
  		send(TableToString(res));
  	  }

  	  //Wait


  	  //Master-drone needs to aggregate
  	  if(master){
  		  vector<Table> reses;
  		  char * a;
  		  //für einen wert, muss erweiter werden durch for loop um mehrere empfangen zu können

  		  char * c1;
  		  receiev(c1);
  		  reses[0] = StringToTable(c1);

  		  vector<int> mod;
  		  vector<string> different_results;
  		  for(int i=0; reses[0].data.size();i++){
  			for(int x =0; reses.size();x++){

  				string r1 = reses[x].data[i].back();
  				auto it = std::find(different_results.begin(), different_results.end(),r1);

  				if(it!=different_results.end()){
  					mod[std::distance(different_results.begin(),it)]++;
  				}else{
  					different_results.push_back(r1);
  					mod.push_back(1);
  				}
  			}
  		  }
  		  //Find mode in mod
  		  int endresult;
  		  endresult= *max_element(mod.begin(),mod.end());

  		  //Send endresult (optional weights for federated learning)
  		 // send(endresult);
  		 // send(endresult);
  	  }


  	  //Receive endresult - For future projects

  	  //recData();
  	  if(!master){
  		  char * a;
  		  receiev(a);
  	  }




    }
    /* USER CODE END 3 */


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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 50;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 38400;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port, CS_I2C_SPI_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(OTG_FS_PowerSwitchOn_GPIO_Port, OTG_FS_PowerSwitchOn_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LD4_Pin|LD3_Pin|LD5_Pin|LD6_Pin
                          |Audio_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : CS_I2C_SPI_Pin */
  GPIO_InitStruct.Pin = CS_I2C_SPI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(CS_I2C_SPI_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : OTG_FS_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = OTG_FS_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(OTG_FS_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PDM_OUT_Pin */
  GPIO_InitStruct.Pin = PDM_OUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
  HAL_GPIO_Init(PDM_OUT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : I2S3_WS_Pin */
  GPIO_InitStruct.Pin = I2S3_WS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
  HAL_GPIO_Init(I2S3_WS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : SPI1_SCK_Pin SPI1_MISO_Pin SPI1_MOSI_Pin */
  GPIO_InitStruct.Pin = SPI1_SCK_Pin|SPI1_MISO_Pin|SPI1_MOSI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : BOOT1_Pin */
  GPIO_InitStruct.Pin = BOOT1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BOOT1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : CLK_IN_Pin */
  GPIO_InitStruct.Pin = CLK_IN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
  HAL_GPIO_Init(CLK_IN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD4_Pin LD3_Pin LD5_Pin LD6_Pin
                           Audio_RST_Pin */
  GPIO_InitStruct.Pin = LD4_Pin|LD3_Pin|LD5_Pin|LD6_Pin
                          |Audio_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : I2S3_MCK_Pin I2S3_SCK_Pin I2S3_SD_Pin */
  GPIO_InitStruct.Pin = I2S3_MCK_Pin|I2S3_SCK_Pin|I2S3_SD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : VBUS_FS_Pin */
  GPIO_InitStruct.Pin = VBUS_FS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(VBUS_FS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : OTG_FS_ID_Pin OTG_FS_DM_Pin OTG_FS_DP_Pin */
  GPIO_InitStruct.Pin = OTG_FS_ID_Pin|OTG_FS_DM_Pin|OTG_FS_DP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : OTG_FS_OverCurrent_Pin */
  GPIO_InitStruct.Pin = OTG_FS_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(OTG_FS_OverCurrent_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Audio_SCL_Pin Audio_SDA_Pin */
  GPIO_InitStruct.Pin = Audio_SCL_Pin|Audio_SDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : MEMS_INT2_Pin */
  GPIO_InitStruct.Pin = MEMS_INT2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(MEMS_INT2_GPIO_Port, &GPIO_InitStruct);

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
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

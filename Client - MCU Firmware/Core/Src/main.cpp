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
#include <cstring>
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

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){



}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */

/**
  * @brief  The application entry point.
  * @retval int
  */




  


  int send (char * txData){
  //
  int bytesToSend =10+strlen(txData);
  char send[10000];


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



  void receievCPP(char * arg){
  	char txData[100];
      while (1){
    	HAL_UART_Receive(&huart2,(uint8_t *) buffer_rx,1,1000);
    	if (buffer_rx[0]== (uint8_t) '#')
    		{
    		break;
    		}

    	}

    	//check for payload length
    	int j=0;
    	char msglen [8];
    	while (1){
    	HAL_UART_Receive(&huart2,(uint8_t *) buffer_rx,1,1000);
    	if (buffer_rx[0]== (uint8_t) '|')
    		{
    		break;
    		}
    	msglen[j]=buffer_rx[0];
    	j= j+1;
    	}

    	int msglength=0;
    	sscanf (msglen, "%d", &msglength);


    	//receive payload
    	HAL_UART_Receive(&huart2,(uint8_t *) buffer_rx,msglength,1000);


    	 int i =0;
    	while (i<msglength){
    	txData[i]= (uint8_t) buffer_rx[i];
    	//buffer_rx[i]=NULL;
    	i=i+1;
    	}


      	strcpy( arg,buffer_rx);
      }





  int receiev (char * txData){
  while (1){
	HAL_UART_Receive(&huart2,(uint8_t *) buffer_rx,1,1000);
	if (buffer_rx[0]== (uint8_t) '#')
		{
		break;
		}

	}

	//check for payload length
	int j=0;
	char msglen [8];
	while (1){
	HAL_UART_Receive(&huart2,(uint8_t *) buffer_rx,1,1000);
	if (buffer_rx[0]== (uint8_t) '|')
		{
		break;
		}
	msglen[j]=buffer_rx[0];
	j= j+1;
	}

	int msglength=0;
	sscanf (msglen, "%d", &msglength);

	

	//receive payload
	HAL_UART_Receive(&huart2,(uint8_t *) buffer_rx,msglength,1000);


	 int i =0;
	while (i<msglength){
	txData[i]=buffer_rx[i];
	buffer_rx[i]=NULL;
	i=i+1;
	}

  	return 1;
  }



  //Ben


/*  void SplitStringH(char* s, vector<char*> &v){

   	char* temp = "";
   	for(int i=0;i<strlen(s);++i){

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

   void SplitStringD(char* s, vector<char*> &v){

     	char* temp = "";
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

   void SplitStringS(char* s, vector<char*> &v){

     	char* temp = "";
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

     }*/



/*  Table StringToTable(char * s1){
 	  vector<string> input;

 	  //may be different depending on libraries
 	  //string slashString = str(s1);
 	  char* slashString(s1);

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
   }*/



  //Ben
  //Test kommentar

    void TableToString(Table t1, char * tableString){
 	  char attrName[1000]  = {};
 	  char data [1000] = {};
 	  char attrValueList [1000] = {};

 	  int attrNameSize = t1.attrName.size();

 	  for(int i = 0; i < attrNameSize; i++){
 		  if(i==0){

 			  sprintf(attrName, "%d", t1.attrName[0]);

 			  //attrName = '0'+ t1.attrName[0];
 		  }else{
 			  strcat(attrName,"#");

 			  char tmp [200];
 			  sprintf(tmp, "%d", t1.attrName[i]);
 			  strcat(attrName,tmp);


 		  }
 	  }

 	  for(int i = 0; i < t1.data.size(); i++){
 		  for(int a = 0; a < t1.data[i].size();a++){
 			  if(a == 0 && i==0){

 				  sprintf(data, "%d", t1.data[i][a]);

 				  //data.append(std::to_string(t1.data[i][a]));
 			  }else{

 				 strcat(data,"#");

 				 char tmp [200];
 				 sprintf(tmp, "%d", t1.data[i][a]);
 				 strcat(data,tmp);

 				  //data.append("#");
 				  //data.append(std::to_string(t1.data[i][a]));
 			  }
 		  }
 		  if(i != t1.data.size()-1){
 			  strcat(data,"$");
 			  //data.append("$");
 		  }
 	  }

 	  for(int i = 0; i < t1.attrValueList.size(); i++){
 	  		  for(int a = 0; a < t1.attrValueList[i].size();a++){
 	  			  if(a == 0 && i==0){
 	  				  sprintf(attrValueList, "%d", t1.attrValueList[i][a]);

 	  				 // data.append(std::to_string(t1.attrValueList[i][a]));
 	  			  }else{


 	  				  	strcat(attrValueList,"#");
 	  					char tmp [200];
 	  					sprintf(tmp, "%d", t1.attrValueList[i][a]);
 	  					strcat(attrValueList,tmp);

 	  				  //data.append("#");
 	  				  //data.append(std::to_string(t1.attrValueList[i][a]));
 	  			  }
 	  		  }
 	  		  if(i != t1.attrValueList.size()-1){
 	  			  strcat(attrValueList,"$");
 	  			  //data.append("$");
 	  		  }
 	  	  }


 	 strcpy (tableString, attrName);
 	 strcat(tableString,"/#");
 	  strcat(tableString,data);
 	 strcat(tableString,"/");
 	  strcat(tableString,attrValueList);
 	/*  final.append("/");
 	  final.append(data);
 	  final.append("/");
 	  final.append(attrValueList);*/

 	  //Char* c = const_cast<char*>(final.c_str());



   }


//interne trennung # - extern $




int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  //MX_DMA_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  //Ben
    /* USER CODE BEGIN 2 */

        vector<int> attrName;
        vector<vector<int> > data;

        vector<vector<int> > attrValueList;

        //examples - need to be adjusted
        attrName = {1,2};
        data ={{0, 60, 402, 19, 0, 2, 2, 13, 0}, {0, 70, 402, 44, 0, 1, 2, 13, 0}, {1, 50, 402, 34, 0, 3, 1, 14, 0}, {0, 60, 402, 24, 0, 1, 1, 14, 0}, {0, 60, 402, 14, 0, 1, 1, 14, 0}, {0, 50, 403, 29, 0, 2, 2, 24, 0}, {1, 40, 403, 19, 1, 3, 2, 13, 0}, {0, 60, 402, 14, 0, 2, 1, 14, 0}, {0, 60, 402, 49, 1, 3, 1, 5, 0}, {0, 50, 402, 14, 0, 1, 1, 13, 0}, {0, 30, 403, 34, 0, 2, 1, 13, 0}, {0, 40, 403, 14, 0, 2, 2, 14, 0}, {0, 60, 402, 24, 0, 2, 2, 13, 0}, {0, 50, 403, 34, 0, 3, 1, 14, 0}, {1, 60, 402, 34, 1, 2, 2, 23, 1}, {1, 50, 403, 34, 0, 3, 1, 23, 0}, {0, 50, 403, 14, 0, 1, 1, 14, 0}, {0, 50, 402, 19, 1, 2, 1, 5, 1}, {0, 50, 402, 29, 1, 3, 2, 13, 0}, {0, 40, 403, 29, 0, 2, 2, 5, 0}, {0, 40, 403, 4, 0, 3, 1, 5, 0}, {0, 40, 403, 29, 999, 2, 1, 24, 1}, {1, 40, 403, 34, 1, 3, 1, 13, 1}, {0, 60, 402, 19, 0, 2, 1, 14, 0}, {0, 50, 401, 19, 0, 2, 1, 14, 0}, {1, 40, 403, 29, 0, 2, 1, 14, 1}, {0, 40, 403, 24, 0, 2, 1, 5, 0}, {0, 50, 402, 24, 0, 3, 1, 13, 0}, {1, 60, 402, 34, 0, 3, 2, 5, 0}, {1, 40, 403, 34, 0, 2, 2, 13, 0}, {1, 40, 403, 29, 0, 3, 1, 13, 0}, {0, 60, 402, 34, 0, 2, 1, 14, 1}, {0, 60, 402, 29, 0, 3, 2, 13, 0},
        		{0, 50, 403, 39, 0, 2, 2, 13, 0},
				{0, 40, 403, 34, 0, 2, 1, 24, 0},
				{0, 30, 403, 29, 1, 2, 2, 13, 1}
        };




        Table table;
        table.attrName=attrName;
        table.data=data;
        table.attrValueList=attrValueList;

        //initializing the DecisionTree
        DecisionTree decTree(table) ;


        //Observation table
        vector<int> obsattrName;
        vector<vector<int> > obsdata;

        vector<vector<int> > obsattrValueList;


        //example - needs to get filled with the data that is received
        obsattrName = {1,2,3,4};
        obsdata = {{0,1,0,0},
          		   {1,0,1,1},
          		   {0,0,0,0}};


        Table obstable;
        obstable.attrName=obsattrName;
        obstable.data=obsdata;
        obstable.attrValueList=obsattrValueList;


        Table res;
        res.attrName=attrName;


        //This bool will decide whether the drone is the master drone
        bool master = false;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  /* USER CODE END WHILE */

	        /* USER CODE BEGIN 3 */

	    	  //Classification

	    	  for(int i=0;i < obstable.data.size(); i++) {
	    	  		vector<int> result = obstable.data[i];
	    	  		result.push_back(decTree.guess(obstable.data[i]));
	    	  		res.data.push_back(result);
	    	  	}

	    	  //Send results of classification to master
	    	  if(!master){
	    		  char  a[10000];
	    		  TableToString(table, a);

	    		  bool equalsRequestCharacter=true;
	    		  	 while (1){
	    		  		char txData[100];
	    		  		receievCPP(txData);
	    		  		 //send(txData);

	    		  		equalsRequestCharacter =true;
	    		  		char right[]="/sent";
	    		  		int i;
	    		  		for (i=0;i<4;i++){
	    		  			if (txData[i]!=right[i]){
	    		  				equalsRequestCharacter=false;
	    		  				break;
	    		  			}
	    		  		}
	    		  		if (equalsRequestCharacter){
	    		  			break;
	    		  		}
	    		  	}

	    		  send(a);

	    	  }

	    	  //Wait


	    	  vector<int> h = res.data[0];
	    	  //vector<int> z = h[0];
	    	  int j = h[4];
	    	  int r = 55;
	    	  vector<int> h1 = res.data[1];
	    	  int f = h1[4];
			  vector<int> h2 = res.data[2];
			  int roh = h2[4];
			  vector<int> h3 = res.data[3];
	          int dah = h3[4];



	    	  //Master-drone needs to aggregate
	    	  if(master){
	    		  vector<Table> reses;
	    		  char * a;
	    		  //für einen wert, muss erweiter werden durch for loop um mehrere empfangen zu können

	    		  char * c1;
	    		  //receiev(c1);
	    		 // reses[0] = StringToTable(c1);


	    		  vector<int> mod;
	    		  vector<int> different_results;
	    		  for(int i=0; reses[0].data.size();i++){
	    			for(int x =0; reses.size();x++){

	    				int r1 = reses[x].data[i].back();
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
	    		  send((char *) endresult);
	    		 // send(endresult);
	    	  }


	    	  //Receive endresult - For future projects

	    	  //recData();
	    	  if(!master){
	    		  char * a;
	    		  receiev(a);
	    		  int z = (int) a;
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
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

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
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */


  /*Configure GPIO pins : LD12_Pin LD13_Pin LD14_Pin LD15_Pin */

  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

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

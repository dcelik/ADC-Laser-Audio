// Set GPIO pin 4 to output


INP_GPIO(27); // must use INP_GPIO before we can use OUT_GPIO
OUT_GPIO(27);

void rasPiSend(char bytes[]){

    for(int i = 0; i < sizeof(bytes); i++){
        for(in j = 0; j < strlen(bytes[i]); j++){
            if(bytes[i][j] == 1){
                GPIO_SET = 1<<27;
            }
            else if(bytes[i][j] == 0){
                GPIO_CLR = 1<<27;
            }
        }
    }
GPIO_CLR = 1<<27;
}
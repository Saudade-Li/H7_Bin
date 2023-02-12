//
// Created by 小李又在摸鱼 on 2022/9/12.
//

#ifndef TEST_SHELL_PORT_H
#define TEST_SHELL_PORT_H


short User_Shell_Write(char *data, unsigned short len);
short User_Shell_Read(char *data, unsigned short len);
void User_Shell_Init(void);

#endif //TEST_SHELL_PORT_H

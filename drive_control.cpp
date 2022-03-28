
#include <iostream>
#include <stdio.h>

#include <chrono>
#include <thread>

#include <boost/asio.hpp>

#include <boost/bind.hpp>
//-------------------------------------------------------------------------------------
// void sendThreadRun(boost::asio::serial_port *serialPort)
// {
// #pragma region //*变量初始化
//     unsigned char sendBuffer[] = {0x55, 0XAA, 0x04, 0x01, 0x03, 0x37, 0x14, 0x05, 0X58};

//     int sum = 0;
//     //char sign = 1;
//     int id;
//     int a; //新增目标位置变量

// #pragma region //*主程序
//     while (true)
//     {
//         //sendBuffer[7] += sign * 0x01;                         //!新增第一行
//         //sign = sendBuffer[7] > (0x05 + sign * 0x03) ? -1 : 1; //!新增第二个字
//         std::cin >> id;
//         std::cin >> a; //输入目标位置，在while循环里可以实现实时控制目标位置，因为这个while是死循环
//         switch (id)
//         {
//         case 1:
//             sendBuffer[3] = {0x01};
//             break;

//         case 2:
//             sendBuffer[3] = {0x02};
//             break;
//         }

//         switch (a)
//         {
//         case 0:
//             sendBuffer[7] = {0x00};
//             break;

//         case 1:
//             sendBuffer[7] = {0x07};
//             sendBuffer[6] = {0xD0};
//             break;
//         }

//         for (size_t i = 2; i < sizeof(sendBuffer) - 1; i++)
//         {
//             sum = sum + sendBuffer[i];
//         }

//         sendBuffer[sizeof(sendBuffer) - 1] = sum;
//         sum = 0;

//         std::this_thread::sleep_for(std::chrono::milliseconds(20));
//         serialPort->write_some(boost::asio::buffer(sendBuffer, sizeof(sendBuffer)));

//         int i = 7;

//         //printf("sendBuffer[%d]=%x\n", i, sendBuffer[i]);
//     }
// #pragma endregion
// }

// //---------------------------------------------------------------------------------------------

// void receiveThreadRun(boost::asio::serial_port *serialPort)
// {
//     unsigned char buff[1024];
//     int readCount = 0;

//     while (true)
//     {
//         memset(buff, 0, sizeof(buff));

//         readCount = serialPort->read_some(boost::asio::buffer(buff, sizeof(buff)));
//         if (readCount)
//         {
//             for (int i = 0; i < readCount; i++)
//             {
//                 //  printf("buff[%d]=%x\n", i, buff[i]);
//             }
//             //std::cout << "---------------------------" << std::endl;
//             readCount = 0;
//         }
//         sleep(2);
//     }
// }

//创建校验和函数
char checkSum(unsigned char *sendBuffer)
{
    int sum = 0;
    for (size_t i = 2; i < sizeof(sendBuffer); i++)
    {
        sum = sum + sendBuffer[i];
    }
    sendBuffer[sizeof(sendBuffer) - 1] = sum;
    sum = 0;
}

int main(int argc, char **argv)
{
    boost::asio::io_service ioService;
    boost::asio::serial_port serialPort(ioService, "/dev/ttyUSB0");

    serialPort.set_option(boost::asio::serial_port::baud_rate(115200));
    serialPort.set_option(boost::asio::serial_port::flow_control(boost::asio::serial_port::flow_control::none));
    serialPort.set_option(boost::asio::serial_port::parity(boost::asio::serial_port::parity::none));
    serialPort.set_option(boost::asio::serial_port::stop_bits(boost::asio::serial_port::stop_bits::one));
    serialPort.set_option(boost::asio::serial_port::character_size(8));

    unsigned char sendBuffer[] = {0x55, 0XAA, 0x04, 0x02, 0x03, 0x37, 0x00, 0x00, 0X58};
    checkSum(sendBuffer);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    serialPort.write_some(boost::asio::buffer(sendBuffer, sizeof(sendBuffer)));

    sendBuffer[6] = {0x14};
    sendBuffer[7] = {0x05};
    checkSum(sendBuffer);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    serialPort.write_some(boost::asio::buffer(sendBuffer, sizeof(sendBuffer)));

    return 0;
}

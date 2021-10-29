#ifndef HARDWARE_COMMUNICATION_LIB__SERIALCOM_HH
#define HARDWARE_COMMUNICATION_LIB__SERIALCOM_HH

/**
 * @file serialcom.hh
 * @brief Simple class library for Serial communication(Send or Receive) in C++ (Not Thread Safe)
 * @author Suisei WADA
 * @date 25th July, 2021
 * 
 * @details
 * @note
**/

#include <string>
#include <memory>
#include <iostream>
#include <boost/asio.hpp>

/**
 * Core class for Serial communication.
**/
namespace hwcomlib
{

  class SerialCom
  {       
    /* Constructor, Destructor */
    public:
      SerialCom( std::string port, unsigned int baudrate );
      ~SerialCom();

    /* Public Mthods, Accessor */
    public:
      //Configuration
      bool setPort( std::string port );
      bool setBaudRate( unsigned int rate );
      bool setCharacterSize( unsigned int size );
      bool setFlowControl( boost::asio::serial_port_base::flow_control::type option );
      bool setParity( boost::asio::serial_port_base::parity::type option );
      bool setStopBits( boost::asio::serial_port_base::stop_bits::type option );

      //Transceive
      void runAsync( void );
      std::size_t sendSync( std::string& buffer ); //Blocking
      std::size_t recvSync( std::string& buffer ); //Blocking
      bool sendAsync( std::string& buffer ); //Non-Blocking
      bool recvAsync( std::string& buffer ); //Non-Blocking

    /* Class member objects */
    private:
      std::unique_ptr<boost::asio::io_service> iosrv_;
      std::unique_ptr<boost::asio::serial_port> serialport_;
      std::unique_ptr<std::thread> thread_async_serialcom_;
  };

}

#endif
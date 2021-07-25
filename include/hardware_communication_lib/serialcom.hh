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
 */

#include <string>
#include <memory>
#include <iostream>
#include <boost/asio.hpp>

/**
 * Core class for Serial communication.
 */
namespace hwcomlib
{

  class SerialCommunicationClass
  {       
    /* Constructor, Destructor */
    public:
      SerialCommunicationClass();
      SerialCommunicationClass( std::string port, int bardrate );
      ~SerialCommunicationClass();

    public:
      void setBaudRate( int rate );
      void setPort( std::string port );
      void send( std::string& buffer );
      void recv( std::string& buffer );

    /* Class member functions */
    private:

    /* Class member objects */
    private:
      std::unique_ptr<boost::asio::serial_port> serial_interface_;

  };

}

#endif
#include "hardware_communication_lib/serialcom.hh"
//Referenced
/* https://blog.myon.info/entry/2015/04/19/boost-asio-serial/ */
/* http://blog.livedoor.jp/k_yon/archives/52145222.html */

namespace hwcomlib
{
  SerialCom::SerialCom( std::string port, unsigned int baudrate )
  {
    iosrv_ = std::make_unique<boost::asio::io_service>();
    serialport_ = std::make_unique<boost::asio::serial_port>( iosrv_, port.c_str() );

    serialport_->set_option( boost::asio::serial_port_base::baud_rate( baudrate ) );
    serialport_->set_option( boost::asio::serial_port_base::character_size( 8 ) );
    serialport_->set_option( boost::asio::serial_port_base::flow_control( boost::asio::serial_port_base::flow_control::none ) );
    serialport_->set_option( boost::asio::serial_port_base::parity( boost::asio::serial_port_base::parity::none ) );
    serialport_->set_option( boost::asio::serial_port_base::stop_bits( boost::asio::serial_port_base::stop_bits::one ) );
  }


  SerialCom::~SerialCom()
  {
    if( serialport_->is_open() ){ serialport_->close(); }
  }


  bool SerialCom::setPort( std::string port )
  {
    if( serialport_->is_open() ){ serialport_->close(); }
    serialport_->open( port.c_str() );
  }

  bool SerialCom::setBaudRate( unsigned int rate )
  {
    if( serialport_ == nullptr ){ return false; }
    else{ serialport_->set_option( boost::asio::serial_port_base::baud_rate( rate ) ); }

    return true;
  }


  bool SerialCom::setCharacterSize( unsigned int size )
  {
    if( serialport_ == nullptr ){ return false; }
    else{ serialport_->set_option( boost::asio::serial_port_base::character_size( size ) ); }

    return true;
  }


  bool SerialCom::setFlowControl( boost::asio::serial_port_base::flow_control::type option )
  {
    if( serialport_ == nullptr ){ return false; }
    else{ serialport_->set_option( boost::asio::serial_port_base::flow_control( option ) ); }

    return true;
  }


  bool SerialCom::setParity( boost::asio::serial_port_base::parity::type option )
  {
    if( serialport_ == nullptr ){ return false; }
    else{ serialport_->set_option( boost::asio::serial_port_base::parity( option ) ); }

    return true;
  }


  bool SerialCom::setStopBits( boost::asio::serial_port_base::stop_bits::type option )
  {
    if( serialport_ == nullptr ){ return false; }
    else{ serialport_->set_option( boost::asio::serial_port_base::stop_bits( option ) ); }

    return true;
  }


  void SerialCom::runAsync( void )
  {
    thread_async_serialcom_ = std::make_unique<std::thread>( iosrv_->run() );
  }


  std::size_t SerialCom::sendSync( std::string& buffer )
  {
    std::size_t send_size = serialport_->write_some( boost::asio::buffer( buffer ) );

    return send_size;
  }


  std::size_t SerialCom::recvSync( std::string& buffer )
  {
    std::size_t recv_size = serialport_->read_some( boost::asio::buffer( buffer ) );

    return recv_size;
  }


}
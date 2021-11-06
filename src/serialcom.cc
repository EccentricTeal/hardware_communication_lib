#include "hardware_communication_lib/serialcom.hh"
//Referenced
/* https://blog.myon.info/entry/2015/04/19/boost-asio-serial/ */
/* http://blog.livedoor.jp/k_yon/archives/52145222.html */
/* https://amedama1x1.hatenablog.com/entry/2015/12/14/000000_1 */
/* https://yutopp.hateblo.jp/entry/2011/12/15/001518 */

namespace hwcomlib
{
  SerialCom::SerialCom( std::string port, unsigned int baudrate )
  {
    serialport_ = std::make_unique<boost::asio::serial_port>( iosrv_, port.c_str() );

    serialport_->set_option( boost::asio::serial_port_base::baud_rate( baudrate ) );
    serialport_->set_option( boost::asio::serial_port_base::character_size( 8 ) );
    serialport_->set_option( boost::asio::serial_port_base::flow_control( boost::asio::serial_port_base::flow_control::none ) );
    serialport_->set_option( boost::asio::serial_port_base::parity( boost::asio::serial_port_base::parity::none ) );
    serialport_->set_option( boost::asio::serial_port_base::stop_bits( boost::asio::serial_port_base::stop_bits::one ) );
  }


  SerialCom::~SerialCom()
  {
    //iosrv_.stop(); <- Executed by destructor of io_service::work. If stop, the thread to execute iosrv_.run(), is also gointg to stop.
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


  void SerialCom::run( void )
  {
    if( iosrv_work_ )
    {
      ;
    }
    else
    {
      iosrv_.reset();//For case of re-running
      iosrv_work_ = std::make_unique<boost::asio::io_service::work>( iosrv_ );
      thread_async_serialcom_ = std::make_unique<std::thread>( [this]{ iosrv_.run(); } );
    }
  }

  void SerialCom::stop( void )
  {
    if( iosrv_work_ ){ iosrv_work_->~work(); }
    if( thread_async_serialcom_->joinable() ){ thread_async_serialcom_->join(); }
  }


  void SerialCom::dispatchSend( char* buffer, std::function<void( const boost::system::error_code&, std::size_t )> handler )
  {
    serialport_->async_write_some( boost::asio::buffer( buffer, sizeof(buffer) ), std::bind( handler, std::placeholders::_1, std::placeholders::_2 ) );
  }


  void SerialCom::dispatchRecv( char* buffer, std::function<void( const boost::system::error_code&, std::size_t )> handler )
  {
    serialport_->async_read_some( boost::asio::buffer( buffer, sizeof(buffer) ), std::bind( handler, std::placeholders::_1, std::placeholders::_2 ) );
  }


}
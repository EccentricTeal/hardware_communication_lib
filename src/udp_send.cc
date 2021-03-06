#include "hardware_communication_lib/udpcom.hh"

namespace hwcomlib
{
  UdpSend::UdpSend( std::string dest_ip, uint16_t dest_port ):
  iosrv_ptr_( new boost::asio::io_service )
  {
    //Initializing Socket
    socket_ptr_ = std::make_unique<boost::asio::ip::udp::socket>( *iosrv_ptr_ );
    socket_ptr_->open( boost::asio::ip::udp::v4() );
    setDestEndpoint( dest_ip, dest_port );
  }


  UdpSend::~UdpSend()
  {
    socket_ptr_->close();
  }


  void UdpSend::setDestEndpoint( std::string dest_ip, uint16_t dest_port )
  {
    boost::asio::ip::address_v4 ip_addr = boost::asio::ip::address_v4::from_string( dest_ip );
    dest_endpoint_ = boost::asio::ip::udp::endpoint( ip_addr, dest_port );
  }


  int32_t UdpSend::sendData( std::string send_data )
  {
    const size_t sent = socket_ptr_->send_to( boost::asio::buffer( send_data ), dest_endpoint_ );

    return 0;
  }
}
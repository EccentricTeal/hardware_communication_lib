#include "hardware_communication_lib/udpcom.hh"

namespace hwcomlib
{
  UdpRecv::UdpRecv( uint16_t udp_port ):
  iosrv_ptr_( new boost::asio::io_service )
  {
    //Initializing Socket
    socket_ptr_ = std::make_unique<boost::asio::ip::udp::socket>( *iosrv_ptr_ );
    socket_ptr_->open( boost::asio::ip::udp::v4() );
  }


  UdpRecv::~UdpRecv()
  {
    socket_ptr_->close();
  }


  std::tuple<size_t, std::string> UdpRecv::recvData( std::string src_ip, std::vector<char>& buffer )
  {
    /* Local Variables Declaration */
    boost::asio::ip::udp::endpoint src_endpoint;
    std::string recv_ipaddr;

    /* Initializing Local Variables */
    buffer.clear();

    /* Receive UDP Message (Block) */
    size_t sent = socket_ptr_->receive_from( boost::asio::buffer(buffer), src_endpoint );
    recv_ipaddr = src_endpoint.address().to_string();

    if( recv_ipaddr != src_ip )
    {
      buffer.clear();
      return std::make_tuple( 0, recv_ipaddr );
    }
    else
    {
      ;
    }

    return std::make_tuple( sent, recv_ipaddr );
  }

}


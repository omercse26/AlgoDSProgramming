
#define BOOST_THREAD_USE_LIB 
#include <iostream>
#include <boost/asio.hpp>
#include <string>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <map>

using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;

char buff[100] = "Connected to the server.";            
static int num_clients;

class connection;
map<int, connection*> connect_map;

struct connection
{
	tcp::socket sock;
        int client_id;
        io_service& ios;
        bool connected;
        int connect_to;
	connection(io_service& ios, int client_id): sock(ios), client_id(client_id)
                ,ios(ios), connected (false) {}
        
        void start()
        {                    
            // Send a client list to the currently connected client
            stringstream client_list;
            client_list << "clientlist:";
            for (int i=0; i < num_clients; i++)
            {
                if (i != client_id)
                        client_list << i << ":";                
            }           
                
            async_write(sock, boost::asio::buffer(client_list.str()), 
                                boost::bind(&connection::write_handler, this,boost::asio::placeholders::error));           
            
            
            wait_for_connection_request();
            
        }
        void write_handler(const boost::system::error_code &ec) 
	{ 
                cout << buff << " sent to" << client_id << endl;
	}
        
        void wait_for_connection_request()
        {            
            
            cout << client_id << " waiting for connection reply" << endl ;
            sock.async_read_some
                        (boost::asio::buffer(buff,100), 
                        boost::bind(&connection::accept_connection_request, this, boost::asio::placeholders::error));
        }   
        
        void accept_connection_request(const boost::system::error_code &ec)
        {
            cout << client_id << " wants to connect to " ;
            cout << buff << endl;
            int connect_to = boost::lexical_cast<int>(buff);
            (connect_map[connect_to]->sock).async_write_some
                        (boost::asio::buffer(buff,100), 
                        boost::bind(&connection::write_handler, this, boost::asio::placeholders::error));
        }
};	

class server
{
	io_service ios;
	tcp::endpoint endp; 
	tcp::acceptor acceptr;			 
	
public:
       
	server() : endp(tcp::v4(), 1024), 
				acceptr(ios, endp)
	{            
                // We cannot use the same socket again. New socket for every request.
                connection* sock = new connection(ios, num_clients);
                connect_map[num_clients] = sock;
		acceptr.async_accept(sock->sock,
                        boost::bind(&server::accept_handler, this, boost::asio::placeholders::error, sock));                                                  
		ios.run();	                                                          
	}
	
	void accept_handler(const boost::system::error_code &ec, connection* sock) 
	{                
		if (!ec) 
		{
			cout << "new client " << num_clients++ << " arrived." <<endl;
                        boost::thread new_client(boost::bind(&connection::start, sock));
                        //sock->start();
			
		} 
                connection* new_sock = new connection(ios, num_clients);
                connect_map[num_clients] = new_sock;
                acceptr.async_accept(new_sock->sock,
                        boost::bind(&server::accept_handler, this, boost::asio::placeholders::error, new_sock));  
	} 
		
};	

int main()
{

	new server();
        cout << "Server ended" << endl;
        cin.ignore();
	return 0;
}


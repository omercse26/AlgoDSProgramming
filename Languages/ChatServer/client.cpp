#define BOOST_THREAD_USE_LIB 
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>
#include <string>
#include <windows.h>
using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;

boost::array<char, 4096> buff; 
char line[100];

io_service global_ios;

class client 
{
    io_service& ios;
    tcp::resolver::query qry;
    tcp::resolver rslv;
    tcp::socket sock;
    tcp::endpoint endp;
    vector<int> client_list;
    enum STATE {NOTCHATTING, CHATTING};
    int state;    
    
public:
    bool connected;
    client() : ios(global_ios), qry("localhost","1024"), rslv(ios), sock(ios), state(NOTCHATTING)
                , connected (false)
    {
         tcp::resolver::iterator dest = rslv.resolve(qry);
         tcp::resolver::iterator end_dest ;
         
         //Destination endpoint is at the last after resolving server address
         while ( dest != end_dest ) {
                endp = *dest++;                
         }
         sock.async_connect (endp, boost::bind(&client::connect_handler, this, boost::asio::placeholders::error));    
         //ios.run();                
    }
    
    void read_handler(const boost::system::error_code &ec) 
    {             
                if (!ec) 
                { 
                       parse_message();                           
                } 
                sock.async_read_some
                        (boost::asio::buffer(buff,100), 
                        boost::bind(&client::read_handler, this, boost::asio::placeholders::error));
    } 
    void parse_message()
    {
        typedef boost::tokenizer<boost::char_separator<char> > tokenizer;         
        
        cout << "bytes we got " << string(buff.data()) << endl;
        boost::char_separator<char> sep(":");
        std::string s = buff.data();
        tokenizer tok(s,sep); 
      
        bool client_list_message = false;
        for (tokenizer::iterator it = tok.begin(); it != tok.end(); ++it)                 
        {
            //cout << "current ken from " << *it << endl;
            if ((*it).compare("clientlist") != 0 && client_list_message == false)
                break;
            else if ((*it).compare ("clientlist") == 0)
            {
                client_list_message = true;
                continue;
            }
            
           //client_list.push_back(boost::lexical_cast<int>(*it));                    
        }
        
        /*if (client_list_message == false)
            cout << buff << endl;
         */
    }

    void connect_handler(const boost::system::error_code& ErrorCode)
    {
        connected = true;
        if (ErrorCode)
                cout << "error found\n";    
        sock.async_read_some(boost::asio::buffer(buff,100), boost::bind(&client::read_handler, this, boost::asio::placeholders::error));    
    }
    
    void write()
    {
                        
         sock.async_write_some(buffer(line, strlen(line)),
                boost::bind(&client::write_handler, this, boost::asio::placeholders::error));    
         
    }
    
    void write_handler(const boost::system::error_code &ec) 
    {
        cout << "Message Sent" << endl;
        
        /*                 
         sock.async_write_some(buffer(line, strlen(line)),
                boost::bind(&client::read_handler, this, boost::asio::placeholders::error));    
         */
        
    }
    
};

int main() {

    client cl;
    
    boost::thread t(boost::bind(&io_service::run, &global_ios));
    
    while (cl.connected == false)   
        Sleep(1000);    
    
    cout << "Connected" << endl;    
    cout << "Select one of the client to Chat with:" ;
    cin.getline(line, 100);    
    cl.write();
    
    
    /* while (cin.getline(line, 100))
    {
     cl.write();
    }
     */
    
    cin.ignore();
    t.join();
    return 0;
}

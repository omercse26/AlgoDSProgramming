#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include "boost/filesystem.hpp"
#include "boost/regex.hpp"

using namespace std;
using namespace boost::filesystem;
using namespace std;
vector<string> tokenize(const string& str, const string& delim, bool include_delim)
{
    size_t pos = 0,not_delim,nextspace;
    vector<string> vec;
    char a;

    while (pos != string::npos)
    {
           nextspace = str.find_first_of(delim,pos);
           not_delim = str.find_first_not_of(delim,pos);

           if (include_delim)
           {
               // if it is one character and that too delimeter
               if (nextspace == string::npos && not_delim == string::npos)
                   break;

               if (nextspace != string::npos && nextspace < not_delim)
                   // there is delimiter before and we cannot ignore it.
               {
                   vec.push_back(string(1,str[nextspace]));
                   pos = nextspace+1;
                   continue; // there can be a delimeter again
               }
           }
           if (not_delim == string::npos)
              not_delim = str.length() - 1;

           nextspace = str.find_first_of(delim,not_delim+1);

           if (nextspace != string::npos)
             {
                //cout << "Tokenize: " << str[nextspace] <<endl;             
                vec.push_back (str.substr(not_delim,nextspace - not_delim));
                if (include_delim)
                   vec.push_back(string(1,str[nextspace]));
                pos = nextspace+1;
             }
           else
             {
               if (str.length() == 1) // I need this check for one character string
                   vec.push_back (str.substr(not_delim));
               else  if ((str.length() - 1 - not_delim) > 0 || not_delim == (str.length()-1))
                   vec.push_back (str.substr(not_delim));
                pos = string::npos;
             }
    }
    return vec;
}

class FileBuffer
{
  ifstream input;
  string regex;
  vector<string> buffer;
  vector<string>::const_iterator it;
public:

  FileBuffer(const char* s,string reg): regex(reg) { it = buffer.end();input.open(s); }

  bool gettoken(string& s, int* newline)
  {     
      string str;
      *newline = 0;
      s = "";
      if ( it == buffer.end())
        {             
           int valid = readline(str);
           //str+="\n";
           *newline = 1;
           if (valid == 0)
            {
                buffer = tokenize(str, regex,true);
                buffer.push_back("\n");
                //cout << "Vector ";
                //for (vector<string>::iterator ts = buffer.begin(); ts != buffer.end(); ts++)
                //{
                //    cout  << *ts << " : ";
                //}
                //cout << endl;
                it = buffer.begin(); 
                if (it == buffer.end())
                 {
                   s = "";
                   return true;
                }
           }
           else
             return false;
         }
         s = *it;
         it++;               
         return true;                                       
  }

  int readline(string& s)
  {                                           
        if (input.is_open())
           if (input.good())
                {
                      getline(input, s);
                      return 0;
               }
               else
                {
                  input.close();
                  return -1;
               }
  }
};



void stripcomments(const char* in, const char* out)

{
    FileBuffer buf(in, "/*");
    ofstream output(out);
    string s;
    int i=0;
    int new_line =0;
    string temp;

start0:    
    while (buf.gettoken(s, &new_line))
    {    
start:       
        if (s.find_first_not_of(" ",0) != string::npos)
        {         
            temp = s;
            if (s=="/")
            {
                if (!buf.gettoken(s, &new_line))
                {
                    output.close(); return;
                }
                else if (s == "*")
                {                   
                    i=1;                   
                    while(buf.gettoken(s,&new_line))
                    {
                        if (s == "/")
                        {
                            buf.gettoken(s,&new_line);
                            if ( s == "*")
                            {
                                i++;
                            }
                        }
                        else if (s == "*")
                        {
                            buf.gettoken(s,&new_line);
                            if (s == "/")
                                i--;
                            if (i == 0)
                                goto start0;
                        }
                    }
                    //goto start;
                }
                else if (s == "/" && new_line == 0)
                {
                    while(buf.gettoken(s,&new_line))
                    {
                        if (new_line == 1)
                            break;
                    }
                    goto start;
                }
                temp+=s;
            }            
            if (i == 0)
            {
                output << temp;
            }
        }
        //s.~basic_string();
    }
    output.close();
}

bool isspace(string s)
{
    size_t a = s.find_first_not_of(" ",0);
    if (a == string::npos)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void findexit(const char* s,const char* final)
{
    ofstream out(final);
    ifstream in(s);
    string line;
    
    while(in.good())
    {
        
        getline(in, line);
        size_t ret_pos = line.find("return");
        if (ret_pos != string::npos)
        {
        string before_ret = line.substr(0,ret_pos);
        string after_ret = line.substr(ret_pos);
        string final_string = "{"+before_ret+ "std::cout << \" exiting \" << __FUNCTION__ <<endl;\n" + after_ret+"}";
        line = final_string;
        }
        out << line << endl;
    }
    in.close();
    out.close();
    
}

void findentry_exit(const char* in, const char* out)

{

    FileBuffer buf(in, "(){};");
    ofstream output(out);
    string token;
    int newline;
    int i,j;

getentry:
    while (buf.gettoken(token,&newline))
    {
                output <<token;
                if (token == "(")
                {
                                i = 1;
                                while(1)
                {
                                buf.gettoken(token,&newline);
                                output  << token;
                                  while (token=="\n" || isspace(token))
                                {
                                      buf.gettoken(token,&newline);
                                      output << token;
                                }
                                if (token == "(")
                                     i++;
                                else if (token == ")")
                                {
                                     --i;
                                     if (i == 0)
                                        break;
                                }
                }
                buf.gettoken(token,&newline);
                                output <<  token;
                                while (token=="\n" || isspace(token))
                                {
                                      buf.gettoken(token,&newline);
                                      output << token;
                                }
                                if (token != "{")
                                   goto getentry;
                                else if (token == "{")
                                {
                                                j = 1;
                        output << "\nstd::cout << \"entering \" << __FUNCTION__ << std::endl;" << endl;
                              while (1)
                              {
                                  string first, second;
                                  buf.gettoken(token,&newline);
                                  first = token;
                                    while (token=="\n" || isspace(token))
                                    {
                                      buf.gettoken(token,&newline);                                     
                                      second += token;
                                     }
                                  if (token == "{")
                                  {
                                     j++;
                                  }
                                  else if (token == "}")
                                  {
                                        j--;
                                       if (j ==0) {                                            
                                           first += second;
                                           first = "\nstd::cout << \"exiting \" << __FUNCTION__ << std::endl;" + first;
                                           output << first;
                                           break;
                                       }
                                  }
                                  first += second;
                                  output <<  first;
                                  
                        }
                   }
}
}
output.close();
}

const boost::regex my_filter( ".*\.cpp" );
vector<path> cppfiles;

void recursefiles(path p)
{   
     
     if ( !exists( p ) ) return;

     if (is_regular_file(p))
     {
         boost::smatch what;
         if( boost::regex_match( p.string(), what, my_filter ) )
         {
           cout <<"File      " << p << endl;
           cppfiles.push_back(p);
         }
     }
     else if (is_directory(p))

     {
         directory_iterator end_itr;
         cout <<"Directory " << p << endl;

         for (directory_iterator it(p); it != end_itr; it++)
             recursefiles(it->path());

     }
}
int main()

{
    //stripcomments("test\\TestReporterStdout.cpp", "test\\TestReporterStdout1.cpp");
     //findentry_exit("test\\TestReporterStdout1.cpp", "test\\TestReporterStdout2.cpp");
    boost::filesystem::path p("D:\\CP.00\\CP.00_dev_ref\\docusp\\dcmark\\kmarker\\src");
    recursefiles(p);
    
    for (vector<path>::iterator it = cppfiles.begin(); it!=cppfiles.end(); it++)
    {
        string str = (*it).filename().string();
        size_t end = str.find_first_of(".", 0);
        string name = str.substr(0,end);
        string pth = (*it).parent_path().string();
        string ext = (*it).extension().string();
        
        string file1 = (*it).string();
        string file2 = pth+"\\"+name+"1"+ext;
        string file3 = pth+"\\"+name+"2"+ext;
        string file4 = pth+"\\"+name+"3"+ext;
        
        cout <<  file1 << ":" << file2 <<":"<< file3 <<endl;
        
        stripcomments(file1.c_str(), file2.c_str());
        findentry_exit(file2.c_str(), file3.c_str());
        findexit(file3.c_str(),file4.c_str());
        
        return 0;
    }
}

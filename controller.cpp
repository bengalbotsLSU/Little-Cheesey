#include "data.hpp"
#include "tcp_client.hpp" 
#include <string> 
#include <thread>
#include <cstdlib> 
#include <unistd.h> 
#include <fcntl.h> 
#include <mutex>

const char* file_handle = "/dev/input/js0";

data::input parse_input(unsigned short key, unsigned short value);
bool is_relevant_input(unsigned short key);

int main(){
    data::shared_state state = {
        .buffer = std::list<data::input>(),
        .write_index = 0,
        .read_index = 0
    };
    state.reading = false;
    state.writing = false;
    std::mutex m;
    
    auto tcp_thread = std::thread(start_tcp, std::ref(state), std::ref(m));
    
    auto file_desc = open(file_handle, O_RDONLY); //maybe O_NONBLOCK
    if(file_desc == -1){
      std::cerr << "Error opening file, likely permissions related." << std::endl;
      tcp_thread.join();
      return -1;
    }
    std::cout << "ready to read" << std::endl;
    while(true){

      unsigned short arr_data[4];
      auto num_bytes = read(file_desc, arr_data, 8);
      if(num_bytes == 8 && is_relevant_input(arr_data[3])){
	printf("Locking\n");
	m.lock();
        state.buffer.push_back(data::input{ .key=arr_data[3], .value=arr_data[2]});

	m.unlock();
	printf("Unlocking\n");
	}
       else {
	std::cout << num_bytes << std::endl;
       }
    }
    std::cout << "Out of loop" << std::endl;
    tcp_thread.join();
    return 0;
}

bool is_relevant_input(unsigned short key){
  
  switch (key){
    case 0x702:
    case 0x201:
    case 0xA01:
    case 0x401:
    case 0x501:
      return true;
    default:
      return false;
  }
}

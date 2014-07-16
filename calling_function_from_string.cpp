#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <functional>
#include <stdexcept>
#include <type_traits>

// for proper evaluation of the stream extraction to the arguments
template<class R>
struct invoker{
  R result;
  template<class F, class... Args>
  invoker(F&& f, Args&&... args)
    : result(f(std::forward<Args>(args)...)) {}
};

template<>
struct invoker<void>{
  template<class F, class... Args>
  invoker(F&& f, Args&&... args)
  { f(std::forward<Args>(args)...); }
};

template<class F, class Sig>
struct stream_function_;

template<class F, class R, class... Args>
struct stream_function_<F, R(Args...)>{
  stream_function_(F f)
    : _f(f) {}

  void operator()(std::istream& args, std::string* out_opt) const{
    call(args, out_opt, std::is_void<R>());
  }

private:  
  template<class T>
  static T get(std::istream& args){
    T t; // must be default constructible
    if(!(args >> t)){
      args.clear();
      throw std::invalid_argument("invalid argument to stream_function");
    }
    return t;
  }

  // void return
  void call(std::istream& args, std::string*, std::true_type) const{
    invoker<void>{_f, get<Args>(args)...};
  }

  // non-void return
  void call(std::istream& args, std::string* out_opt, std::false_type) const{
    if(!out_opt) // no return wanted, redirect
      return call(args, nullptr, std::true_type());

    std::stringstream conv;
    if(!(conv << invoker<R>{_f, get<Args>(args)...}.result))
      throw std::runtime_error("bad return in stream_function");
    *out_opt = conv.str();
  }

  F _f;
};

template<class Sig, class F>
stream_function_<F, Sig> stream_function(F f){ return {f}; }

typedef std::function<void(std::istream&, std::string*)> func_type;
typedef std::map<std::string, func_type> dict_type;

void print(){
  std::cout << "print()\n";
}

int add(int a, int b){
  return a + b;
}

int sub(int a, int b){
  return a - b;
}

int main(){
  dict_type func_dict;
  func_dict["print"] = stream_function<void()>(print);
  func_dict["add"] = stream_function<int(int,int)>(add);
  func_dict["sub"] = stream_function<int(int,int)>(sub);

  for(;;){
    std::cout << "Which function should be called?\n";
    std::string tmp;
    std::cin >> tmp;
    auto it = func_dict.find(tmp);
    if(it == func_dict.end()){
      std::cout << "Invalid function '" << tmp << "'\n";
      continue;
    }
    tmp.clear();
    try{
      it->second(std::cin, &tmp);
    }catch(std::exception const& e){
      std::cout << "Error: '" << e.what() << "'\n";
      std::cin.ignore();
      continue;
    }
    std::cout << "Result: " << (tmp.empty()? "none" : tmp) << '\n';
  }
}
#include <Rcpp.h>
#include <string>
// #define ASIO_STANDALONE
#include <websocketpp/transport/asio/base.hpp>

//' @export
// [[Rcpp::export]]
std::string get_error_message() {
  using namespace websocketpp::transport::asio::error;
  value val = pass_through;
  websocketpp::lib::error_code ec = make_error_code(val);
  std::string msg = ec.message();
  return msg;
}

//' @export
// [[Rcpp::export]]
int cplusplus() {
  return __cplusplus;
}

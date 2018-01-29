#include <boost/spirit/include/qi.hpp>

namespace xylitol
{
namespace core
{
void print(const char c)
{
  std::cout << c << std::endl;
}
}
}

int main()
{
  using namespace boost::spirit::qi;
  std::string s = R"(<a>)";
  auto fst = s.begin();
  parse(fst, s.end(), '>' >> char_('a')[&xylitol::core::print]);
  return 0;
}

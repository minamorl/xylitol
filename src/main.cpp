#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

namespace xylitol
{
namespace rule
{
template <typename Iterator>
struct lang : qi::grammar<Iterator>
{
  lang() : lang::base_type(document)
  {
    character %= (+qi::char_('a', 'z'))[&lang::print_];
    document %= +('<' >> character >> '>' | qi::char_);
  }
  qi::rule<Iterator> character;
  qi::rule<Iterator> document;

private:
  static void print_(std::vector<char> v)
  {
    std::cout << "Parsing: " << std::string(v.begin(), v.end()) << std::endl;
  }
};
}
}

int main()
{
  std::string s = "<a>xxx<abc>";
  std::string::iterator fst = s.begin();

  xylitol::rule::lang<std::string::iterator> l;

  qi::parse(fst, s.end(), l);
}

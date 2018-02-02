#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

namespace xylitol
{
namespace rule
{

template <typename Iterator>
struct character : qi::grammar<Iterator>
{
};

// Characters
//const auto letter = basechar | ideographic;
const auto basechar = qi::copy(
    qi::char_(u'\u0041', u8'\u005A') | qi::char_(u'\u0061', u'\u007A') | qi::char_(u'\u00C0', u'\u00D6') | qi::char_(u'\u00D8', u'\u00F6') | qi::char_(u'\u00F8', u'\u00FF') | qi::char_(u'\u0100', u'\u0131') | qi::char_(u'\u0134', u'\u013E') | qi::char_(u'\u0141', u'\u0148') | qi::char_(u'\u014A', u'\u017E') | qi::char_(u'\u0180', u'\u01C3') | qi::char_(u'\u01CD', u'\u01F0') | qi::char_(u'\u01F4', u'\u01F5') | qi::char_(u'\u01FA', u'\u0217') | qi::char_(u'\u0250', u'\u02A8') | qi::char_(u'\u02BB', u'\u02C1') | qi::char_(u'\u0386') | qi::char_(u'\u0388', u'\u038A') | qi::char_(u'\u038C') | qi::char_(u'\u038E', u'\u03A1') | qi::char_(u'\u03A3', u'\u03CE') | qi::char_(u'\u03D0', u'\u03D6') | qi::char_(u'\u03DA') | qi::char_(u'\u03DC') | qi::char_(u'\u03DE') | qi::char_(u'\u03E0') | qi::char_(u'\u03E2', u'\u03F3') | qi::char_(u'\u0401', u'\u040C') | qi::char_(u'\u040E', u'\u044F') | qi::char_(u'\u0451', u'\u045C') | qi::char_(u'\u045E', u'\u0481') | qi::char_(u'\u0490', u'\u04C4') | qi::char_(u'\u04C7', u'\u04C8') | qi::char_(u'\u04CB', u'\u04CC') | qi::char_(u'\u04D0', u'\u04EB') | qi::char_(u'\u04EE', u'\u04F5') | qi::char_(u'\u04F8', u'\u04F9') | qi::char_(u'\u0531', u'\u0556') | qi::char_(u'\u0559') | qi::char_(u'\u0561', u'\u0586') | qi::char_(u'\u05D0', u'\u05EA') | qi::char_(u'\u05F0', u'\u05F2') | qi::char_(u'\u0621', u'\u063A') | qi::char_(u'\u0641', u'\u064A') | qi::char_(u'\u0671', u'\u06B7') | qi::char_(u'\u06BA', u'\u06BE') | qi::char_(u'\u06C0', u'\u06CE') | qi::char_(u'\u06D0', u'\u06D3') | qi::char_(u'\u06D5') | qi::char_(u'\u06E5', u'\u06E6') | qi::char_(u'\u0905', u'\u0939') | qi::char_(u'\u093D') | qi::char_(u'\u0958', u'\u0961') | qi::char_(u'\u0985', u'\u098C') | qi::char_(u'\u098F', u'\u0990') | qi::char_(u'\u0993', u'\u09A8') | qi::char_(u'\u09AA', u'\u09B0') | qi::char_(u'\u09B2') | qi::char_(u'\u09B6', u'\u09B9') | qi::char_(u'\u09DC', u'\u09DD') | qi::char_(u'\u09DF', u'\u09E1') | qi::char_(u'\u09F0', u'\u09F1') | qi::char_(u'\u0A05', u'\u0A0A') | qi::char_(u'\u0A0F', u'\u0A10') | qi::char_(u'\u0A13', u'\u0A28') | qi::char_(u'\u0A2A', u'\u0A30') | qi::char_(u'\u0A32', u'\u0A33') | qi::char_(u'\u0A35', u'\u0A36') | qi::char_(u'\u0A38', u'\u0A39') | qi::char_(u'\u0A59', u'\u0A5C') | qi::char_(u'\u0A5E') | qi::char_(u'\u0A72', u'\u0A74') | qi::char_(u'\u0A85', u'\u0A8B') | qi::char_(u'\u0A8D') | qi::char_(u'\u0A8F', u'\u0A91') | qi::char_(u'\u0A93', u'\u0AA8') | qi::char_(u'\u0AAA', u'\u0AB0') | qi::char_(u'\u0AB2', u'\u0AB3') | qi::char_(u'\u0AB5', u'\u0AB9') | qi::char_(u'\u0ABD') | qi::char_(u'\u0AE0') | qi::char_(u'\u0B05', u'\u0B0C') | qi::char_(u'\u0B0F', u'\u0B10') | qi::char_(u'\u0B13', u'\u0B28') | qi::char_(u'\u0B2A', u'\u0B30') | qi::char_(u'\u0B32', u'\u0B33') | qi::char_(u'\u0B36', u'\u0B39') | qi::char_(u'\u0B3D') | qi::char_(u'\u0B5C', u'\u0B5D') | qi::char_(u'\u0B5F', u'\u0B61') | qi::char_(u'\u0B85', u'\u0B8A') | qi::char_(u'\u0B8E', u'\u0B90') | qi::char_(u'\u0B92', u'\u0B95') | qi::char_(u'\u0B99', u'\u0B9A') | qi::char_(u'\u0B9C') | qi::char_(u'\u0B9E', u'\u0B9F') | qi::char_(u'\u0BA3', u'\u0BA4') | qi::char_(u'\u0BA8', u'\u0BAA') | qi::char_(u'\u0BAE', u'\u0BB5') | qi::char_(u'\u0BB7', u'\u0BB9') | qi::char_(u'\u0C05', u'\u0C0C') | qi::char_(u'\u0C0E', u'\u0C10') | qi::char_(u'\u0C12', u'\u0C28') | qi::char_(u'\u0C2A', u'\u0C33') | qi::char_(u'\u0C35', u'\u0C39') | qi::char_(u'\u0C60', u'\u0C61') | qi::char_(u'\u0C85', u'\u0C8C') | qi::char_(u'\u0C8E', u'\u0C90') | qi::char_(u'\u0C92', u'\u0CA8') | qi::char_(u'\u0CAA', u'\u0CB3') | qi::char_(u'\u0CB5', u'\u0CB9') | qi::char_(u'\u0CDE') | qi::char_(u'\u0CE0', u'\u0CE1') | qi::char_(u'\u0D05', u'\u0D0C') | qi::char_(u'\u0D0E', u'\u0D10') | qi::char_(u'\u0D12', u'\u0D28') | qi::char_(u'\u0D2A', u'\u0D39') | qi::char_(u'\u0D60', u'\u0D61') | qi::char_(u'\u0E01', u'\u0E2E') | qi::char_(u'\u0E30') | qi::char_(u'\u0E32', u'\u0E33') | qi::char_(u'\u0E40', u'\u0E45') | qi::char_(u'\u0E81', u'\u0E82') | qi::char_(u'\u0E84') | qi::char_(u'\u0E87', u'\u0E88') | qi::char_(u'\u0E8A') | qi::char_(u'\u0E8D') | qi::char_(u'\u0E94', u'\u0E97') | qi::char_(u'\u0E99', u'\u0E9F') | qi::char_(u'\u0EA1', u'\u0EA3') | qi::char_(u'\u0EA5') | qi::char_(u'\u0EA7') | qi::char_(u'\u0EAA', u'\u0EAB') | qi::char_(u'\u0EAD', u'\u0EAE') | qi::char_(u'\u0EB0') | qi::char_(u'\u0EB2', u'\u0EB3') | qi::char_(u'\u0EBD') | qi::char_(u'\u0EC0', u'\u0EC4') | qi::char_(u'\u0F40', u'\u0F47') | qi::char_(u'\u0F49', u'\u0F69') | qi::char_(u'\u10A0', u'\u10C5') | qi::char_(u'\u10D0', u'\u10F6') | qi::char_(u'\u1100') | qi::char_(u'\u1102', u'\u1103') | qi::char_(u'\u1105', u'\u1107') | qi::char_(u'\u1109') | qi::char_(u'\u110B', u'\u110C') | qi::char_(u'\u110E', u'\u1112') | qi::char_(u'\u113C') | qi::char_(u'\u113E') | qi::char_(u'\u1140') | qi::char_(u'\u114C') | qi::char_(u'\u114E') | qi::char_(u'\u1150') | qi::char_(u'\u1154', u'\u1155') | qi::char_(u'\u1159') | qi::char_(u'\u115F', u'\u1161') | qi::char_(u'\u1163') | qi::char_(u'\u1165') | qi::char_(u'\u1167') | qi::char_(u'\u1169') | qi::char_(u'\u116D', u'\u116E') | qi::char_(u'\u1172', u'\u1173') | qi::char_(u'\u1175') | qi::char_(u'\u119E') | qi::char_(u'\u11A8') | qi::char_(u'\u11AB') | qi::char_(u'\u11AE', u'\u11AF') | qi::char_(u'\u11B7', u'\u11B8') | qi::char_(u'\u11BA') | qi::char_(u'\u11BC', u'\u11C2') | qi::char_(u'\u11EB') | qi::char_(u'\u11F0') | qi::char_(u'\u11F9') | qi::char_(u'\u1E00', u'\u1E9B') | qi::char_(u'\u1EA0', u'\u1EF9') | qi::char_(u'\u1F00', u'\u1F15') | qi::char_(u'\u1F18', u'\u1F1D') | qi::char_(u'\u1F20', u'\u1F45') | qi::char_(u'\u1F48', u'\u1F4D') | qi::char_(u'\u1F50', u'\u1F57') | qi::char_(u'\u1F59') | qi::char_(u'\u1F5B') | qi::char_(u'\u1F5D') | qi::char_(u'\u1F5F', u'\u1F7D') | qi::char_(u'\u1F80', u'\u1FB4') | qi::char_(u'\u1FB6', u'\u1FBC') | qi::char_(u'\u1FBE') | qi::char_(u'\u1FC2', u'\u1FC4') | qi::char_(u'\u1FC6', u'\u1FCC') | qi::char_(u'\u1FD0', u'\u1FD3') | qi::char_(u'\u1FD6', u'\u1FDB') | qi::char_(u'\u1FE0', u'\u1FEC') | qi::char_(u'\u1FF2', u'\u1FF4') | qi::char_(u'\u1FF6', u'\u1FFC') | qi::char_(u'\u2126') | qi::char_(u'\u212A', u'\u212B') | qi::char_(u'\u212E') | qi::char_(u'\u2180', u'\u2182') | qi::char_(u'\u3041', u'\u3094') | qi::char_(u'\u30A1', u'\u30FA') | qi::char_(u'\u3105', u'\u312C') | qi::char_(u'\uAC00', u'\uD7A3'));

/*
ideographic
combiningchar
digit
extender;
*/
}
}

int main()
{
  std::string s = "<a>xxx<abc>";
  std::string::iterator fst = s.begin();

  qi::parse(fst, s.end(), &xylitol::rule::basechar);
  return 0;
}

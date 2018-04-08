#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

namespace xylitol
{
namespace rule
{

// External Subset
const auto extsubsetdecl = qi::copy(
  *( markupdecl | conditionalsect | pereference | s ));
const auto extsubset = qi::copy(-extDecl >> extsubsetdecl);
// Standalone Document Declaration
const auto sddecl = qi::copy(s >> qi::string("standalone") >> eq 
  >> (qi::char_('\'') >> (qi::string("yes") | qi::string("no")) >> qi::char_('\'') | 
  qi::char_('"')) >> (qi::string("yes") | qi::string("no")) >> qi::char_('"'));

/*
// Language Identification
const auto iso639code = (qi::char_('a', 'z') | qi::char_('A', 'Z')) >> (qi::char_('a', 'z') | qi::char_('A', 'Z'));
const auto ianacode = (qi::char_('i') | qi::char_('I')) >> '-' >> +qi::char_('A', 'Z');
const auto usercode = (qi::char_('x') | qi::char_('X')) >> '-' >> +qi::char_('A', 'Z');
const auto subcode = +(qi::char_('a', 'z') | qi::char_('A', 'Z'));
const auto languageid = langcode >> *("-" > subcode);
const auto langcode = iso639code | ianacode | usercode;

// Element
const auto element = emptyelemtag | stag >> content >> etag;

// Start-tag
const auto stag = "<" >> name >> *(s >> attribute) >> -s >> ">";
const auto attribute = name >> eq >> attvalue;

// End-tag
const auto etag = "</" >> name >> -s >> ">";

// Content of Elements
const auto content = *(element | chardata | reference | cdsect | pi | comment);

// Tags for Empty Children
const auto emptyelemtag = "<" >> name >> *(s >> attribute) >> -s >> "/>";

// Element Type Declaration
const auto elementdecl = "<!ELEMENT" >> s >> name >> s >> contentspec >> -s >> '>';
const auto contentspec = qi::string("EMPTY") | qi::string("ANY") | mixed | children;

// Element-content Models
const auto choise = qi::copy('(' >> -s >> cp >> *(-s >> '|' >> -s >> cp) >> -s >> ')');
const auto seq = qi::copy('(' >> -s >> cp >> *(-s >> ',' >> -s >> cp) >> -s >> ')');
const auto children = qi::copy(choise | seq) >> -(qi::char_('?') | qi::char_('*') | qi::char_('+'));
const auto cp = qi::copy((name | choise | seq) >> -(qi::char_('?') | qi::char_('*') | qi::char_('+')));

// Mixed-content Declaration
const auto mixed = qi::copy(
  "(" >> -s >> "#PCDATA" >> *(-s >> "|" >> -s >> name) >> -s >> ")*" | "(" >> -s >> "#PCDATA" >> -s >> ")"
);

// Attribute-list Declaration
const auto attlistdecl = qi::copy("<!ATTLIST" >> s >> name >> *attdef >> -s >> ">");
const auto attdef = qi::copy(s >> name >> s >> atttype >> s >> defaultdecl);

// Attribute Types
const auto stringtype = qi::copy(qi::string("CDATA"));
const auto tokenizedtype = qi::copy(qi::string("ID") | "IDREF" | "IDREFS" | "ENTITY" | "ENTITIES" | "NMTOKEN" | "NMTOKENS");
const auto atttype = qi::copy(stringtype | tokenizedtype | enumeratedtype);

// Enumerated Attribute Types
const auto notationtype = qi::copy("NOTATION" >> s >> "(" >> -s >> name >>
                                   *(-s >> "|" >> -s >> name) >> ")");
const auto enumeration = qi::copy("(" >> -s >> nmtoken >> *(-s >> "|" >> -s >> nmtoken) >> -s >> ")");
const auto enumeratedtype = qi::copy(notationtype | enumeration);

// Attribute Defaults
const auto defaultdecl = qi::copy(qi::string("#REQUIRED") | qi::string("#IMPLIED") | (-("#FIXED" >> s) >> attvalue));

// Conditional Section (* should be modified *)
const auto includesect = qi::copy(
  "<![" >> -s >> "INCLUDE" >> -s >> "[" >> extsubsetdecl >> "]]"
);
const auto ignoresect = qi::copy(
  "<![" >> -s >> "IGNORE" >> -s >> "[" >> *ignoresectcontents >> "]]>"
);
const auto ignoresectcontents = qi::copy(
  ignore >> *("<![" >> qi::lazy(&ignoresectcontents) >> "]]>" >> ignore)
);
const auto ignore = *character - (*character >> ("<![" || "]]>") >> *character);
const auto conditionalsect = qi::copy(includesect | ignoresect);

// Character Reference
const auto charref = qi::copy(
"&#" >> +qi::char_(0, 9) >> ";" | "&#x" >> +(qi::char_(0,9) | qi::char_('a', 'f') | qi::char_('A', 'F')) >> ";"
);

// Entity Reference
const auto entityref = qi::copy("&" >> name >> ";");
const auto pereference = qi::copy("%" >> name >> ";");
const auto reference = qi::copy(entityref | charref);

// Characters
const auto basechar = qi::copy(
    qi::char_(u'\u0041', u'\u005A') | qi::char_(u'\u0061', u'\u007A') | qi::char_(u'\u00C0', u'\u00D6') | qi::char_(u'\u00D8', u'\u00F6') | qi::char_(u'\u00F8', u'\u00FF') | qi::char_(u'\u0100', u'\u0131') | qi::char_(u'\u0134', u'\u013E') | qi::char_(u'\u0141', u'\u0148') | qi::char_(u'\u014A', u'\u017E') | qi::char_(u'\u0180', u'\u01C3') | qi::char_(u'\u01CD', u'\u01F0') | qi::char_(u'\u01F4', u'\u01F5') | qi::char_(u'\u01FA', u'\u0217') | qi::char_(u'\u0250', u'\u02A8') | qi::char_(u'\u02BB', u'\u02C1') | qi::char_(u'\u0386') | qi::char_(u'\u0388', u'\u038A') | qi::char_(u'\u038C') | qi::char_(u'\u038E', u'\u03A1') | qi::char_(u'\u03A3', u'\u03CE') | qi::char_(u'\u03D0', u'\u03D6') | qi::char_(u'\u03DA') | qi::char_(u'\u03DC') | qi::char_(u'\u03DE') | qi::char_(u'\u03E0') | qi::char_(u'\u03E2', u'\u03F3') | qi::char_(u'\u0401', u'\u040C') | qi::char_(u'\u040E', u'\u044F') | qi::char_(u'\u0451', u'\u045C') | qi::char_(u'\u045E', u'\u0481') | qi::char_(u'\u0490', u'\u04C4') | qi::char_(u'\u04C7', u'\u04C8') | qi::char_(u'\u04CB', u'\u04CC') | qi::char_(u'\u04D0', u'\u04EB') | qi::char_(u'\u04EE', u'\u04F5') | qi::char_(u'\u04F8', u'\u04F9') | qi::char_(u'\u0531', u'\u0556') | qi::char_(u'\u0559') | qi::char_(u'\u0561', u'\u0586') | qi::char_(u'\u05D0', u'\u05EA') | qi::char_(u'\u05F0', u'\u05F2') | qi::char_(u'\u0621', u'\u063A') | qi::char_(u'\u0641', u'\u064A') | qi::char_(u'\u0671', u'\u06B7') | qi::char_(u'\u06BA', u'\u06BE') | qi::char_(u'\u06C0', u'\u06CE') | qi::char_(u'\u06D0', u'\u06D3') | qi::char_(u'\u06D5') | qi::char_(u'\u06E5', u'\u06E6') | qi::char_(u'\u0905', u'\u0939') | qi::char_(u'\u093D') | qi::char_(u'\u0958', u'\u0961') | qi::char_(u'\u0985', u'\u098C') | qi::char_(u'\u098F', u'\u0990') | qi::char_(u'\u0993', u'\u09A8') | qi::char_(u'\u09AA', u'\u09B0') | qi::char_(u'\u09B2') | qi::char_(u'\u09B6', u'\u09B9') | qi::char_(u'\u09DC', u'\u09DD') | qi::char_(u'\u09DF', u'\u09E1') | qi::char_(u'\u09F0', u'\u09F1') | qi::char_(u'\u0A05', u'\u0A0A') | qi::char_(u'\u0A0F', u'\u0A10') | qi::char_(u'\u0A13', u'\u0A28') | qi::char_(u'\u0A2A', u'\u0A30') | qi::char_(u'\u0A32', u'\u0A33') | qi::char_(u'\u0A35', u'\u0A36') | qi::char_(u'\u0A38', u'\u0A39') | qi::char_(u'\u0A59', u'\u0A5C') | qi::char_(u'\u0A5E') | qi::char_(u'\u0A72', u'\u0A74') | qi::char_(u'\u0A85', u'\u0A8B') | qi::char_(u'\u0A8D') | qi::char_(u'\u0A8F', u'\u0A91') | qi::char_(u'\u0A93', u'\u0AA8') | qi::char_(u'\u0AAA', u'\u0AB0') | qi::char_(u'\u0AB2', u'\u0AB3') | qi::char_(u'\u0AB5', u'\u0AB9') | qi::char_(u'\u0ABD') | qi::char_(u'\u0AE0') | qi::char_(u'\u0B05', u'\u0B0C') | qi::char_(u'\u0B0F', u'\u0B10') | qi::char_(u'\u0B13', u'\u0B28') | qi::char_(u'\u0B2A', u'\u0B30') | qi::char_(u'\u0B32', u'\u0B33') | qi::char_(u'\u0B36', u'\u0B39') | qi::char_(u'\u0B3D') | qi::char_(u'\u0B5C', u'\u0B5D') | qi::char_(u'\u0B5F', u'\u0B61') | qi::char_(u'\u0B85', u'\u0B8A') | qi::char_(u'\u0B8E', u'\u0B90') | qi::char_(u'\u0B92', u'\u0B95') | qi::char_(u'\u0B99', u'\u0B9A') | qi::char_(u'\u0B9C') | qi::char_(u'\u0B9E', u'\u0B9F') | qi::char_(u'\u0BA3', u'\u0BA4') | qi::char_(u'\u0BA8', u'\u0BAA') | qi::char_(u'\u0BAE', u'\u0BB5') | qi::char_(u'\u0BB7', u'\u0BB9') | qi::char_(u'\u0C05', u'\u0C0C') | qi::char_(u'\u0C0E', u'\u0C10') | qi::char_(u'\u0C12', u'\u0C28') | qi::char_(u'\u0C2A', u'\u0C33') | qi::char_(u'\u0C35', u'\u0C39') | qi::char_(u'\u0C60', u'\u0C61') | qi::char_(u'\u0C85', u'\u0C8C') | qi::char_(u'\u0C8E', u'\u0C90') | qi::char_(u'\u0C92', u'\u0CA8') | qi::char_(u'\u0CAA', u'\u0CB3') | qi::char_(u'\u0CB5', u'\u0CB9') | qi::char_(u'\u0CDE') | qi::char_(u'\u0CE0', u'\u0CE1') | qi::char_(u'\u0D05', u'\u0D0C') | qi::char_(u'\u0D0E', u'\u0D10') | qi::char_(u'\u0D12', u'\u0D28') | qi::char_(u'\u0D2A', u'\u0D39') | qi::char_(u'\u0D60', u'\u0D61') | qi::char_(u'\u0E01', u'\u0E2E') | qi::char_(u'\u0E30') | qi::char_(u'\u0E32', u'\u0E33') | qi::char_(u'\u0E40', u'\u0E45') | qi::char_(u'\u0E81', u'\u0E82') | qi::char_(u'\u0E84') | qi::char_(u'\u0E87', u'\u0E88') | qi::char_(u'\u0E8A') | qi::char_(u'\u0E8D') | qi::char_(u'\u0E94', u'\u0E97') | qi::char_(u'\u0E99', u'\u0E9F') | qi::char_(u'\u0EA1', u'\u0EA3') | qi::char_(u'\u0EA5') | qi::char_(u'\u0EA7') | qi::char_(u'\u0EAA', u'\u0EAB') | qi::char_(u'\u0EAD', u'\u0EAE') | qi::char_(u'\u0EB0') | qi::char_(u'\u0EB2', u'\u0EB3') | qi::char_(u'\u0EBD') | qi::char_(u'\u0EC0', u'\u0EC4') | qi::char_(u'\u0F40', u'\u0F47') | qi::char_(u'\u0F49', u'\u0F69') | qi::char_(u'\u10A0', u'\u10C5') | qi::char_(u'\u10D0', u'\u10F6') | qi::char_(u'\u1100') | qi::char_(u'\u1102', u'\u1103') | qi::char_(u'\u1105', u'\u1107') | qi::char_(u'\u1109') | qi::char_(u'\u110B', u'\u110C') | qi::char_(u'\u110E', u'\u1112') | qi::char_(u'\u113C') | qi::char_(u'\u113E') | qi::char_(u'\u1140') | qi::char_(u'\u114C') | qi::char_(u'\u114E') | qi::char_(u'\u1150') | qi::char_(u'\u1154', u'\u1155') | qi::char_(u'\u1159') | qi::char_(u'\u115F', u'\u1161') | qi::char_(u'\u1163') | qi::char_(u'\u1165') | qi::char_(u'\u1167') | qi::char_(u'\u1169') | qi::char_(u'\u116D', u'\u116E') | qi::char_(u'\u1172', u'\u1173') | qi::char_(u'\u1175') | qi::char_(u'\u119E') | qi::char_(u'\u11A8') | qi::char_(u'\u11AB') | qi::char_(u'\u11AE', u'\u11AF') | qi::char_(u'\u11B7', u'\u11B8') | qi::char_(u'\u11BA') | qi::char_(u'\u11BC', u'\u11C2') | qi::char_(u'\u11EB') | qi::char_(u'\u11F0') | qi::char_(u'\u11F9') | qi::char_(u'\u1E00', u'\u1E9B') | qi::char_(u'\u1EA0', u'\u1EF9') | qi::char_(u'\u1F00', u'\u1F15') | qi::char_(u'\u1F18', u'\u1F1D') | qi::char_(u'\u1F20', u'\u1F45') | qi::char_(u'\u1F48', u'\u1F4D') | qi::char_(u'\u1F50', u'\u1F57') | qi::char_(u'\u1F59') | qi::char_(u'\u1F5B') | qi::char_(u'\u1F5D') | qi::char_(u'\u1F5F', u'\u1F7D') | qi::char_(u'\u1F80', u'\u1FB4') | qi::char_(u'\u1FB6', u'\u1FBC') | qi::char_(u'\u1FBE') | qi::char_(u'\u1FC2', u'\u1FC4') | qi::char_(u'\u1FC6', u'\u1FCC') | qi::char_(u'\u1FD0', u'\u1FD3') | qi::char_(u'\u1FD6', u'\u1FDB') | qi::char_(u'\u1FE0', u'\u1FEC') | qi::char_(u'\u1FF2', u'\u1FF4') | qi::char_(u'\u1FF6', u'\u1FFC') | qi::char_(u'\u2126') | qi::char_(u'\u212A', u'\u212B') | qi::char_(u'\u212E') | qi::char_(u'\u2180', u'\u2182') | qi::char_(u'\u3041', u'\u3094') | qi::char_(u'\u30A1', u'\u30FA') | qi::char_(u'\u3105', u'\u312C') | qi::char_(u'\uAC00', u'\uD7A3'));
const auto ideographic = qi::copy(qi::char_(u'\u4E00', u'\u9FA5') | qi::char_(u'\u3007') | qi::char_(u'\u3021', u'\u3029'));
const auto combiningchar = qi::copy(qi::char_(u'\u0300', u'\u0345') | qi::char_(u'\u0360', u'\u0361') | qi::char_(u'\u0483', u'\u0486') | qi::char_(u'\u0591', u'\u05A1') | qi::char_(u'\u05A3', u'\u05B9') | qi::char_(u'\u05BB', u'\u05BD') | qi::char_(u'\u05BF') | qi::char_(u'\u05C1', u'\u05C2') | qi::char_(u'\u05C4') | qi::char_(u'\u064B', u'\u0652') | qi::char_(u'\u0670') | qi::char_(u'\u06D6', u'\u06DC') | qi::char_(u'\u06DD', u'\u06DF') | qi::char_(u'\u06E0', u'\u06E4') | qi::char_(u'\u06E7', u'\u06E8') | qi::char_(u'\u06EA', u'\u06ED') | qi::char_(u'\u0901', u'\u0903') | qi::char_(u'\u093C') | qi::char_(u'\u093E', u'\u094C') | qi::char_(u'\u094D') | qi::char_(u'\u0951', u'\u0954') | qi::char_(u'\u0962', u'\u0963') | qi::char_(u'\u0981', u'\u0983') | qi::char_(u'\u09BC') | qi::char_(u'\u09BE') | qi::char_(u'\u09BF') | qi::char_(u'\u09C0', u'\u09C4') | qi::char_(u'\u09C7', u'\u09C8') | qi::char_(u'\u09CB', u'\u09CD') | qi::char_(u'\u09D7') | qi::char_(u'\u09E2', u'\u09E3') | qi::char_(u'\u0A02') | qi::char_(u'\u0A3C') | qi::char_(u'\u0A3E') | qi::char_(u'\u0A3F') | qi::char_(u'\u0A40', u'\u0A42') | qi::char_(u'\u0A47', u'\u0A48') | qi::char_(u'\u0A4B', u'\u0A4D') | qi::char_(u'\u0A70', u'\u0A71') | qi::char_(u'\u0A81', u'\u0A83') | qi::char_(u'\u0ABC') | qi::char_(u'\u0ABE', u'\u0AC5') | qi::char_(u'\u0AC7', u'\u0AC9') | qi::char_(u'\u0ACB', u'\u0ACD') | qi::char_(u'\u0B01', u'\u0B03') | qi::char_(u'\u0B3C') | qi::char_(u'\u0B3E', u'\u0B43') | qi::char_(u'\u0B47', u'\u0B48') | qi::char_(u'\u0B4B', u'\u0B4D') | qi::char_(u'\u0B56', u'\u0B57') | qi::char_(u'\u0B82', u'\u0B83') | qi::char_(u'\u0BBE', u'\u0BC2') | qi::char_(u'\u0BC6', u'\u0BC8') | qi::char_(u'\u0BCA', u'\u0BCD') | qi::char_(u'\u0BD7') | qi::char_(u'\u0C01', u'\u0C03') | qi::char_(u'\u0C3E', u'\u0C44') | qi::char_(u'\u0C46', u'\u0C48') | qi::char_(u'\u0C4A', u'\u0C4D') | qi::char_(u'\u0C55', u'\u0C56') | qi::char_(u'\u0C82', u'\u0C83') | qi::char_(u'\u0CBE', u'\u0CC4') | qi::char_(u'\u0CC6', u'\u0CC8') | qi::char_(u'\u0CCA', u'\u0CCD') | qi::char_(u'\u0CD5', u'\u0CD6') | qi::char_(u'\u0D02', u'\u0D03') | qi::char_(u'\u0D3E', u'\u0D43') | qi::char_(u'\u0D46', u'\u0D48') | qi::char_(u'\u0D4A', u'\u0D4D') | qi::char_(u'\u0D57') | qi::char_(u'\u0E31') | qi::char_(u'\u0E34', u'\u0E3A') | qi::char_(u'\u0E47', u'\u0E4E') | qi::char_(u'\u0EB1') | qi::char_(u'\u0EB4', u'\u0EB9') | qi::char_(u'\u0EBB', u'\u0EBC') | qi::char_(u'\u0EC8', u'\u0ECD') | qi::char_(u'\u0F18', u'\u0F19') | qi::char_(u'\u0F35') | qi::char_(u'\u0F37') | qi::char_(u'\u0F39') | qi::char_(u'\u0F3E') | qi::char_(u'\u0F3F') | qi::char_(u'\u0F71', u'\u0F84') | qi::char_(u'\u0F86', u'\u0F8B') | qi::char_(u'\u0F90', u'\u0F95') | qi::char_(u'\u0F97') | qi::char_(u'\u0F99', u'\u0FAD') | qi::char_(u'\u0FB1', u'\u0FB7') | qi::char_(u'\u0FB9') | qi::char_(u'\u20D0', u'\u20DC') | qi::char_(u'\u20E1') | qi::char_(u'\u302A', u'\u302F') | qi::char_(u'\u3099') | qi::char_(u'\u309A'));
const auto digit = qi::copy(qi::char_(u'\u0030', u'\u0039') | qi::char_(u'\u0660', u'\u0669') | qi::char_(u'\u06F0', u'\u06F9') | qi::char_(u'\u0966', u'\u096F') | qi::char_(u'\u09E6', u'\u09EF') | qi::char_(u'\u0A66', u'\u0A6F') | qi::char_(u'\u0AE6', u'\u0AEF') | qi::char_(u'\u0B66', u'\u0B6F') | qi::char_(u'\u0BE7', u'\u0BEF') | qi::char_(u'\u0C66', u'\u0C6F') | qi::char_(u'\u0CE6', u'\u0CEF') | qi::char_(u'\u0D66', u'\u0D6F') | qi::char_(u'\u0E50', u'\u0E59') | qi::char_(u'\u0ED0', u'\u0ED9') | qi::char_(u'\u0F20', u'\u0F29'));
const auto extender = qi::copy(qi::char_(u'\u00B7') | qi::char_(u'\u02D0') | qi::char_(u'\u02D1') | qi::char_(u'\u0387') | qi::char_(u'\u0640') | qi::char_(u'\u0E46') | qi::char_(u'\u0EC6') | qi::char_(u'\u3005') | qi::char_(u'\u3031', u'\u3035') | qi::char_(u'\u309D', u'\u309E') | qi::char_(u'\u30FC', u'\u30FE'));
const auto letter = qi::copy(basechar | ideographic);

// Entity Declaration
const auto entitydef = qi::copy(entityvalue | externalid >> -ndatadecl);
const auto pedef = qi::copy(entityvalue | externalid);
const auto gedecl = qi::copy("<!ENTITY" >> s >> name >> s >> entitydef >> -s >> ">");
const auto pedecl = qi::copy("<!ENTITY" >> s >> "%" >> s >> name >> s >> pedef >> -s >> ">");
const auto entitydecl = qi::copy(gedecl | pedecl);

// External Entity Declaration
const auto externalid =  qi::copy("SYSTEM" >> s >> systemliteral | "PUBlIC" >> s >> pubidliteral >> s >> systemliteral);
const auto ndatadecl = qi::copy( s >> "NDATA" >> s >> name);

// Text Declaration
const auto textdecl = qi::copy(
"?xml" >> -versioninfo >> encodingdecl >> -s >> "?>"
);

template <typename Iterator>
struct wellformed_external_parsed_entity : qi::grammar<Iterator>
{
  wellformed_external_parsed_entity() : wellformed_external_parsed_entity::base_type(encname)
  {
    extparsedent %= -textdecl >> content;
    extpe %= -textdecl >> extsubsetdecl;
  }
  qi::rule<Iterator> extparsedent;
  qi::rule<Iterator> extpe;
};

template <typename Iterator>
struct encoding_declaration : qi::grammar<Iterator>
{
  encoding_declaration() : encoding_declaration::base_type(encname)
  {
    encodingdecl %= s >> "encoding" >> eq >> ("\"" >> encname >> "\"" | "'" >> encname "'");
    encname %= char_('A', 'z') >>
               *((char_('A', 'z') | char_('0', '9') | char_('.') | char_('_')) | char_('-'));
  }
  qi::rule<Iterator> encname;
  qi::rule<Iterator> encodingdecl;
};

template <typename Iterator>
struct notation_declaration : qi::grammar<Iterator>
{
  notation_declaration() : notation_declaration::base_type(notationdecl)
  {
    publicid %= "PUBLIC" >> s >> pubidliteral;
    notationdecl %= "<!NOTATION" >> s >> name >> s >> (xternalid | publicid) >> -s >> ">";
  }
  qi::rule<Iterator> publicid;
  qi::rule<Iterator> notationdecl;
};
*/
}
}

int main()
{
  std::string s = "<a>xxx<abc>";
  std::string::iterator fst = s.begin();

  // qi::parse(fst, s.end(), &xylitol::rule::basechar);
  return 0;
}

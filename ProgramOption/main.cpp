#include "ProgramOption.h"

#include <iostream>
using namespace std;

namespace config
{
    // default options
    string normal_default;
    string optional_default ;
    vector<string> list_default;

    // keys
    string long_key;
    string short_key;
    string both_key;
    string invisible_key;

    // types
    bool type_bool;
    int type_int;
    double type_double;
    string type_string;

    string no_arg;

    void show_value() {
#define show(x) (cerr << #x ": " << x << endl)
        show(normal_default);
        show(optional_default);
        cerr << "list_default: " ;
        for (int i=0;i<list_default.size();++i) cerr << (i==0?"":", ") << list_default[i] ; cerr << endl;

        // keys
        show(long_key);
        show(short_key);
        show(both_key);
        show(invisible_key);

        // types
        show(type_bool);
        show(type_int);
        show(type_double);
        show(type_string);

        show(no_arg);

    } 

}


int main(int argc, char* argv[])
{
    ProgramOption po(argv[0], "test Program Option");
    using namespace config;   

    po.addOption(Option(normal_default, load<string>)
        .is_default_arg("normal")
        .description("test for normal default option")
        );
    po.addOption(Option(optional_default, load<string>)
        .is_default_arg("optional")
        .is_optional()
        .description("test for optional default option")
        );
    po.addOption(Option(list_default, load2< vector<string> >)
        .is_default_arg("list")
        .is_optional()
        .is_arg_list()
        .description("test for list type default option")
        );
    po.addOption(Option(po.invoke_help(cerr)).keys("help", 'h').no_arg().description("show help message"));
    
    po.addOption(Option(long_key, load<string>)
        .long_key("long")
        .description("option with only long key")
        );
    po.addOption(Option(short_key, load<string>)
        .short_key('s')
        .description("option with only short key")
        );
    po.addOption(Option(both_key, load<string>)
        .keys("both", 'b')
        .description("option with only both long and short key")
        );
    po.addOption(Option(invisible_key, load<string>)
        .long_key("invisible")
        .invisible()
        .description("option invisible in help")
        );
    po.addOption(Option(new ValueSetter<string>(no_arg, "N"))
        .keys("no_arg", 'N')
        .no_arg()
        .description("option without arg")
        );

    po.addOption(Option(type_bool, load<bool>)
        .keys("bool", 'B')
        .description("option with bool type")
        );
    po.addOption(Option(type_int, load<int>)
        .keys("int", 'I')
        .description("option with int type")
        );
    po.addOption(Option(type_double, load<double>)
        .keys("double", 'D')
        .description("option with double type")
        );
    po.addOption(Option(type_string, load<string>)
        .keys("string", 'S')
        .description("option with string type")
        );

    if (!po.parse(argc, argv)) {
        cerr << po.getError() << endl;
        cerr << po.usage() ;
        exit(1);
    }

    show_value();

    return 0;
}
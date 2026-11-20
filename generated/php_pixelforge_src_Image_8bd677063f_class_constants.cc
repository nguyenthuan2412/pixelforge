#include <cstring>
#include <phpx.h>
#include <phpx_helper.h>
#include <phpx_big_int.h>
#include <phpx_big_float.h>
#include <phpx_decimal.h>
#include <phpx_python.h>
#include <typephp_helper.h>
#include <typephp_fiber_generator.h>
#include <phpx_std.h>
#include <php_pixelforge_runtime_decl.h>
#include <php_pixelforge_src_Image_8bd677063f_decl.h>
#include <php_pixelforge_src_pixelforge_7188de8b65_decl.h>

namespace typephp_project_pixelforge {

zend_never_inline void typephp_request_init_class_constant_c568b9d60239c363114a() {
do {
class_const__pixelforge__gravity__ALIASES = php::Array{
    { get_str(1).str(), php::Var(get_str(0)) }, 
    { get_str(0).str(), php::Var(get_str(0)) }, 
    { get_str(3).str(), php::Var(get_str(2)) }, 
    { get_str(5).str(), php::Var(get_str(4)) }, 
    { get_str(6).str(), php::Var(get_str(4)) }, 
    { get_str(8).str(), php::Var(get_str(7)) }, 
    { get_str(10).str(), php::Var(get_str(9)) }, 
    { get_str(11).str(), php::Var(get_str(9)) }, 
    { get_str(13).str(), php::Var(get_str(12)) }, 
    { get_str(15).str(), php::Var(get_str(14)) }, 
    { get_str(16).str(), php::Var(get_str(14)) }, 
    { get_str(18).str(), php::Var(get_str(17)) }, 
    { get_str(20).str(), php::Var(get_str(19)) }, 
    { get_str(21).str(), php::Var(get_str(19)) }, 
    { get_str(2).str(), php::Var(get_str(2)) }, 
    { get_str(4).str(), php::Var(get_str(4)) }, 
    { get_str(7).str(), php::Var(get_str(7)) }, 
    { get_str(9).str(), php::Var(get_str(9)) }, 
    { get_str(12).str(), php::Var(get_str(12)) }, 
    { get_str(14).str(), php::Var(get_str(14)) }, 
    { get_str(17).str(), php::Var(get_str(17)) }, 
    { get_str(19).str(), php::Var(get_str(19)) }, 
    { get_str(22).str(), php::Var(get_str(22)) }, 
    { get_str(23).str(), php::Var(get_str(23)) }
};
php::updateConstant("PixelForge\\Gravity", "ALIASES", php::Array{
    { get_str(1).str(), php::Var(get_str(0)) }, 
    { get_str(0).str(), php::Var(get_str(0)) }, 
    { get_str(3).str(), php::Var(get_str(2)) }, 
    { get_str(5).str(), php::Var(get_str(4)) }, 
    { get_str(6).str(), php::Var(get_str(4)) }, 
    { get_str(8).str(), php::Var(get_str(7)) }, 
    { get_str(10).str(), php::Var(get_str(9)) }, 
    { get_str(11).str(), php::Var(get_str(9)) }, 
    { get_str(13).str(), php::Var(get_str(12)) }, 
    { get_str(15).str(), php::Var(get_str(14)) }, 
    { get_str(16).str(), php::Var(get_str(14)) }, 
    { get_str(18).str(), php::Var(get_str(17)) }, 
    { get_str(20).str(), php::Var(get_str(19)) }, 
    { get_str(21).str(), php::Var(get_str(19)) }, 
    { get_str(2).str(), php::Var(get_str(2)) }, 
    { get_str(4).str(), php::Var(get_str(4)) }, 
    { get_str(7).str(), php::Var(get_str(7)) }, 
    { get_str(9).str(), php::Var(get_str(9)) }, 
    { get_str(12).str(), php::Var(get_str(12)) }, 
    { get_str(14).str(), php::Var(get_str(14)) }, 
    { get_str(17).str(), php::Var(get_str(17)) }, 
    { get_str(19).str(), php::Var(get_str(19)) }, 
    { get_str(22).str(), php::Var(get_str(22)) }, 
    { get_str(23).str(), php::Var(get_str(23)) }
});
} while(0);
}

zend_never_inline void typephp_request_clean_class_constant_c568b9d60239c363114a() {
class_const__pixelforge__gravity__ALIASES.unset();
php::updateConstant("PixelForge\\Gravity", "ALIASES", php::null);
}

}  // namespace typephp_project_pixelforge

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


void php_pixelforge__image____construct(php::Object &this_, php::Var handle) {
    zend_class_entry *tmp_var_0 = get_persistent_class(PersistentClassId{0}, get_str(1));

    typephp_write_property_scoped(this_, get_str(0), handle, tmp_var_0);
}

php::Object php_pixelforge__image__fromfile(php::Object &this_, php::Str path, php::Array options) {
    php::Str tmp_var_1;
    php::Var tmp_var_2;
    php::Var tmp_var_3;
    php::Var tmp_var_4;
    php::Int tmp_var_5 = 0;
    php::Var tmp_var_6;
    php::Var tmp_var_7;
    php::Bool tmp_var_8 = 0;
    php::Int tmp_var_9 = 0;
    php::Var tmp_var_10;
    php::Var tmp_var_11;
    php::Int tmp_var_12 = 0;
    php::Var tmp_var_13;
    php::Var tmp_var_14;
    php::Float tmp_var_15 = 0;
    php::Var tmp_var_16;
    php::Var tmp_var_17;
    php::Bool tmp_var_18 = 0;
    php::Var tmp_var_19;
    php::Var tmp_var_20;
    php::Bool tmp_var_21 = 0;
    php::Var tmp_var_22;
    php::Object tmp_var_23;
    zend_class_entry *tmp_var_0 = get_persistent_class(PersistentClassId{0}, get_str(1));

    tmp_var_1 = path;
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(2))}}, tmp_var_3)) {
        tmp_var_2 = tmp_var_3;
    } else {
        tmp_var_2 = get_str(3);
    }
    tmp_var_4 = php::toString(tmp_var_2);
    tmp_var_5 = php::toInt(php_pixelforge__image__limit(this_, options));
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(4))}}, tmp_var_7)) {
        tmp_var_6 = tmp_var_7;
    } else {
        tmp_var_6 = false;
    }
    tmp_var_8 = php::toBool(tmp_var_6);
    tmp_var_9 = php::toInt(php_pixelforge__image__pages(this_, options));
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(5))}}, tmp_var_11)) {
        tmp_var_10 = tmp_var_11;
    } else {
        tmp_var_10 = 0L;
    }
    tmp_var_12 = php::toInt(tmp_var_10);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(6))}}, tmp_var_14)) {
        tmp_var_13 = tmp_var_14;
    } else {
        tmp_var_13 = 0L;
    }
    tmp_var_15 = php::toFloat(tmp_var_13);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(7))}}, tmp_var_17)) {
        tmp_var_16 = tmp_var_17;
    } else {
        tmp_var_16 = false;
    }
    tmp_var_18 = php::toBool(tmp_var_16);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(8))}}, tmp_var_20)) {
        tmp_var_19 = tmp_var_20;
    } else {
        tmp_var_19 = false;
    }
    tmp_var_21 = php::toBool(tmp_var_19);
    tmp_var_22 = php_pixelforge_from_file(tmp_var_1, tmp_var_4, php::toInt(tmp_var_5), php::toBool(tmp_var_8), php::toInt(tmp_var_9), php::toInt(tmp_var_12), php::toFloat(tmp_var_15), php::toBool(tmp_var_18), php::toBool(tmp_var_21));
    tmp_var_1.unset();
    tmp_var_4.unset();
    tmp_var_23 = (php::newObject(tmp_var_0, php::VarList{tmp_var_22}));
    tmp_var_22.unset();
    return tmp_var_23;
}

php::Object php_pixelforge__image__frombuffer(php::Object &this_, php::Str data, php::Array options) {
    php::Str tmp_var_0;
    php::Var tmp_var_1;
    php::Object tmp_var_2;
    php::Str tmp_var_4;
    php::Var tmp_var_5;
    php::Var tmp_var_6;
    php::Var tmp_var_7;
    php::Int tmp_var_8 = 0;
    php::Var tmp_var_9;
    php::Var tmp_var_10;
    php::Bool tmp_var_11 = 0;
    php::Int tmp_var_12 = 0;
    php::Var tmp_var_13;
    php::Var tmp_var_14;
    php::Int tmp_var_15 = 0;
    php::Var tmp_var_16;
    php::Var tmp_var_17;
    php::Float tmp_var_18 = 0;
    php::Var tmp_var_19;
    php::Var tmp_var_20;
    php::Bool tmp_var_21 = 0;
    php::Var tmp_var_22;
    php::Var tmp_var_23;
    php::Bool tmp_var_24 = 0;
    php::Var tmp_var_25;
    php::Object tmp_var_26;
    zend_class_entry *tmp_var_3 = get_persistent_class(PersistentClassId{0}, get_str(1));

    if (php::toBool(php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(9))}}))) {
        tmp_var_0 = data;
        tmp_var_1 = options.get(get_str(9));
        tmp_var_2 = (php_pixelforge__image__fromraw(this_, tmp_var_0, php::deindirect(tmp_var_1)));
        tmp_var_0.unset();
        tmp_var_1.unset();
        return tmp_var_2;
    }
    tmp_var_4 = data;
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(2))}}, tmp_var_6)) {
        tmp_var_5 = tmp_var_6;
    } else {
        tmp_var_5 = get_str(3);
    }
    tmp_var_7 = php::toString(tmp_var_5);
    tmp_var_8 = php::toInt(php_pixelforge__image__limit(this_, options));
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(4))}}, tmp_var_10)) {
        tmp_var_9 = tmp_var_10;
    } else {
        tmp_var_9 = false;
    }
    tmp_var_11 = php::toBool(tmp_var_9);
    tmp_var_12 = php::toInt(php_pixelforge__image__pages(this_, options));
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(5))}}, tmp_var_14)) {
        tmp_var_13 = tmp_var_14;
    } else {
        tmp_var_13 = 0L;
    }
    tmp_var_15 = php::toInt(tmp_var_13);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(6))}}, tmp_var_17)) {
        tmp_var_16 = tmp_var_17;
    } else {
        tmp_var_16 = 0L;
    }
    tmp_var_18 = php::toFloat(tmp_var_16);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(7))}}, tmp_var_20)) {
        tmp_var_19 = tmp_var_20;
    } else {
        tmp_var_19 = false;
    }
    tmp_var_21 = php::toBool(tmp_var_19);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(8))}}, tmp_var_23)) {
        tmp_var_22 = tmp_var_23;
    } else {
        tmp_var_22 = false;
    }
    tmp_var_24 = php::toBool(tmp_var_22);
    tmp_var_25 = php_pixelforge_from_buffer(tmp_var_4, tmp_var_7, php::toInt(tmp_var_8), php::toBool(tmp_var_11), php::toInt(tmp_var_12), php::toInt(tmp_var_15), php::toFloat(tmp_var_18), php::toBool(tmp_var_21), php::toBool(tmp_var_24));
    tmp_var_4.unset();
    tmp_var_7.unset();
    tmp_var_26 = (php::newObject(tmp_var_3, php::VarList{tmp_var_25}));
    tmp_var_25.unset();
    return tmp_var_26;
}

php::Object php_pixelforge__image__fromraw(php::Object &this_, php::Str data, php::Array raw) {
    php::Str tmp_var_1;
    php::Int tmp_var_2 = 0;
    php::Int tmp_var_3 = 0;
    php::Int tmp_var_4 = 0;
    php::Var tmp_var_5;
    php::Var tmp_var_6;
    php::Var tmp_var_7;
    php::Var tmp_var_8;
    php::Var tmp_var_9;
    php::Bool tmp_var_10 = 0;
    php::Var tmp_var_11;
    php::Object tmp_var_12;
    zend_class_entry *tmp_var_0 = get_persistent_class(PersistentClassId{0}, get_str(1));

    tmp_var_1 = data;
    tmp_var_2 = php::toInt(raw.get(get_str(10)));
    tmp_var_3 = php::toInt(raw.get(get_str(11)));
    tmp_var_4 = php::toInt(raw.get(get_str(12)));
    if (php::exists(raw, {{php::ArrayDimFetch, php::Var(get_str(13))}}, tmp_var_6)) {
        tmp_var_5 = tmp_var_6;
    } else {
        tmp_var_5 = get_str(14);
    }
    tmp_var_7 = php::toString(tmp_var_5);
    if (php::exists(raw, {{php::ArrayDimFetch, php::Var(get_str(15))}}, tmp_var_9)) {
        tmp_var_8 = tmp_var_9;
    } else {
        tmp_var_8 = false;
    }
    tmp_var_10 = php::toBool(tmp_var_8);
    tmp_var_11 = php_pixelforge_from_raw(tmp_var_1, php::toInt(tmp_var_2), php::toInt(tmp_var_3), php::toInt(tmp_var_4), tmp_var_7, php::toBool(tmp_var_10));
    tmp_var_1.unset();
    tmp_var_7.unset();
    tmp_var_12 = (php::newObject(tmp_var_0, php::VarList{tmp_var_11}));
    tmp_var_11.unset();
    return tmp_var_12;
}

php::Object php_pixelforge__image__create(php::Object &this_, php::Array options) {
    php::Array c;
    php::Var tmp_var_0;
    php::Var tmp_var_1;
    php::Var tmp_var_2;
    php::Object tmp_var_3;
    php::Var noise;
    php::Var tmp_var_4;
    php::Var tmp_var_5;
    php::Int tmp_var_7 = 0;
    php::Int tmp_var_8 = 0;
    php::Var tmp_var_9;
    php::Var tmp_var_10;
    php::Int tmp_var_11 = 0;
    php::Var tmp_var_12;
    php::Var tmp_var_13;
    php::Var tmp_var_14;
    php::Var tmp_var_15;
    php::Var tmp_var_16;
    php::Var tmp_var_17;
    php::Var tmp_var_18;
    php::Var tmp_var_19;
    php::Var tmp_var_20;
    php::Float tmp_var_21 = 0;
    php::Var tmp_var_22;
    php::Var tmp_var_23;
    php::Float tmp_var_24 = 0;
    php::Var tmp_var_25;
    php::Object tmp_var_26;
    zend_class_entry *tmp_var_6 = get_persistent_class(PersistentClassId{0}, get_str(1));
    Z_PTR_P(tmp_var_3.ptr()) = get_persistent_class(PersistentClassId{1}, get_str(26));

    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(16))}}, tmp_var_1)) {
        tmp_var_0 = tmp_var_1;
    } else {
        tmp_var_0 = php::Array{
        php::Var(0L), 
        php::Var(0L), 
        php::Var(0L), 
        php::Var(1L)
    };
    }
    tmp_var_2 = tmp_var_0;
    c = php_pixelforge__color__parse(tmp_var_3, tmp_var_2);
    tmp_var_2.unset();
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(17))}}, tmp_var_5)) {
        tmp_var_4 = tmp_var_5;
    } else {
        tmp_var_4 = php::Array{};
    }
    noise = tmp_var_4;
    tmp_var_7 = php::toInt(options.get(get_str(10)));
    tmp_var_8 = php::toInt(options.get(get_str(11)));
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(12))}}, tmp_var_10)) {
        tmp_var_9 = tmp_var_10;
    } else {
        tmp_var_9 = 4L;
    }
    tmp_var_11 = php::toInt(tmp_var_9);
    tmp_var_12 = c.get(0L);
    tmp_var_13 = c.get(1L);
    tmp_var_14 = c.get(2L);
    tmp_var_15 = c.get(3L);
    if (php::exists(noise, {{php::ArrayDimFetch, php::Var(get_str(23))}}, tmp_var_17)) {
        tmp_var_16 = tmp_var_17;
    } else {
        tmp_var_16 = php::empty_string;
    }
    tmp_var_18 = php::toString(tmp_var_16);
    if (php::exists(noise, {{php::ArrayDimFetch, php::Var(get_str(24))}}, tmp_var_20)) {
        tmp_var_19 = tmp_var_20;
    } else {
        tmp_var_19 = 128L;
    }
    tmp_var_21 = php::toFloat(tmp_var_19);
    if (php::exists(noise, {{php::ArrayDimFetch, php::Var(get_str(25))}}, tmp_var_23)) {
        tmp_var_22 = tmp_var_23;
    } else {
        tmp_var_22 = 30L;
    }
    tmp_var_24 = php::toFloat(tmp_var_22);
    tmp_var_25 = php_pixelforge_create(php::toInt(tmp_var_7), php::toInt(tmp_var_8), php::toInt(tmp_var_11), php::toFloatArgExact(php::deindirect(tmp_var_12), get_str(18), 4, get_str(19)), php::toFloatArgExact(php::deindirect(tmp_var_13), get_str(18), 5, get_str(20)), php::toFloatArgExact(php::deindirect(tmp_var_14), get_str(18), 6, get_str(21)), php::toFloatArgExact(php::deindirect(tmp_var_15), get_str(18), 7, get_str(22)), tmp_var_18, php::toFloat(tmp_var_21), php::toFloat(tmp_var_24));
    tmp_var_12.unset();
    tmp_var_13.unset();
    tmp_var_14.unset();
    tmp_var_15.unset();
    tmp_var_18.unset();
    tmp_var_26 = (php::newObject(tmp_var_6, php::VarList{tmp_var_25}));
    tmp_var_25.unset();
    return tmp_var_26;
}

php::Object php_pixelforge__image__text(php::Object &this_, php::Array options) {
    php::Var tmp_var_1;
    php::Var tmp_var_2;
    php::Var tmp_var_3;
    php::Var tmp_var_4;
    php::Var tmp_var_5;
    php::Var tmp_var_6;
    php::Var tmp_var_7;
    php::Var tmp_var_8;
    php::Var tmp_var_9;
    php::Int tmp_var_10 = 0;
    php::Var tmp_var_11;
    php::Var tmp_var_12;
    php::Int tmp_var_13 = 0;
    php::Var tmp_var_14;
    php::Var tmp_var_15;
    php::Var tmp_var_16;
    php::Var tmp_var_17;
    php::Var tmp_var_18;
    php::Bool tmp_var_19 = 0;
    php::Var tmp_var_20;
    php::Var tmp_var_21;
    php::Int tmp_var_22 = 0;
    php::Var tmp_var_23;
    php::Var tmp_var_24;
    php::Bool tmp_var_25 = 0;
    php::Var tmp_var_26;
    php::Var tmp_var_27;
    php::Int tmp_var_28 = 0;
    php::Var tmp_var_29;
    php::Var tmp_var_30;
    php::Var tmp_var_31;
    php::Var tmp_var_32;
    php::Object tmp_var_33;
    zend_class_entry *tmp_var_0 = get_persistent_class(PersistentClassId{0}, get_str(1));

    tmp_var_1 = php::toString(options.get(get_str(27)));
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(28))}}, tmp_var_3)) {
        tmp_var_2 = tmp_var_3;
    } else {
        tmp_var_2 = php::empty_string;
    }
    tmp_var_4 = php::toString(tmp_var_2);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(29))}}, tmp_var_6)) {
        tmp_var_5 = tmp_var_6;
    } else {
        tmp_var_5 = php::empty_string;
    }
    tmp_var_7 = php::toString(tmp_var_5);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(10))}}, tmp_var_9)) {
        tmp_var_8 = tmp_var_9;
    } else {
        tmp_var_8 = 0L;
    }
    tmp_var_10 = php::toInt(tmp_var_8);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(11))}}, tmp_var_12)) {
        tmp_var_11 = tmp_var_12;
    } else {
        tmp_var_11 = 0L;
    }
    tmp_var_13 = php::toInt(tmp_var_11);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(30))}}, tmp_var_15)) {
        tmp_var_14 = tmp_var_15;
    } else {
        tmp_var_14 = get_str(31);
    }
    tmp_var_16 = php::toString(tmp_var_14);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(32))}}, tmp_var_18)) {
        tmp_var_17 = tmp_var_18;
    } else {
        tmp_var_17 = false;
    }
    tmp_var_19 = php::toBool(tmp_var_17);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(33))}}, tmp_var_21)) {
        tmp_var_20 = tmp_var_21;
    } else {
        tmp_var_20 = 0L;
    }
    tmp_var_22 = php::toInt(tmp_var_20);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(34))}}, tmp_var_24)) {
        tmp_var_23 = tmp_var_24;
    } else {
        tmp_var_23 = false;
    }
    tmp_var_25 = php::toBool(tmp_var_23);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(35))}}, tmp_var_27)) {
        tmp_var_26 = tmp_var_27;
    } else {
        tmp_var_26 = 0L;
    }
    tmp_var_28 = php::toInt(tmp_var_26);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(36))}}, tmp_var_30)) {
        tmp_var_29 = tmp_var_30;
    } else {
        tmp_var_29 = get_str(37);
    }
    tmp_var_31 = php::toString(tmp_var_29);
    tmp_var_32 = php_pixelforge_text(tmp_var_1, tmp_var_4, tmp_var_7, php::toInt(tmp_var_10), php::toInt(tmp_var_13), tmp_var_16, php::toBool(tmp_var_19), php::toInt(tmp_var_22), php::toBool(tmp_var_25), php::toInt(tmp_var_28), tmp_var_31);
    tmp_var_1.unset();
    tmp_var_4.unset();
    tmp_var_7.unset();
    tmp_var_16.unset();
    tmp_var_31.unset();
    tmp_var_33 = (php::newObject(tmp_var_0, php::VarList{tmp_var_32}));
    tmp_var_32.unset();
    return tmp_var_33;
}

php::Object php_pixelforge__image__join(php::Object &this_, php::Array inputs, php::Array options) {
    php::Array bg;
    php::Var tmp_var_0;
    php::Var tmp_var_1;
    php::Var tmp_var_2;
    php::Object tmp_var_3;
    php::Object img;
    php::Var tmp_var_5;
    php::Var tmp_var_6;
    php::Bool tmp_var_7 = 0;
    php::Var tmp_var_8;
    php::Var tmp_var_9;
    php::Int tmp_var_10 = 0;
    php::Var tmp_var_11;
    php::Var tmp_var_12;
    php::Int tmp_var_13 = 0;
    php::Var tmp_var_14;
    php::Var tmp_var_15;
    php::Var tmp_var_16;
    php::Var tmp_var_17;
    php::Var tmp_var_18;
    php::Var tmp_var_19;
    php::Var tmp_var_20;
    php::Var tmp_var_21;
    php::Var tmp_var_22;
    php::Var tmp_var_23;
    php::Var tmp_var_24;
    php::Var in;
    php::Var tmp_var_26;
    php::Object tmp_var_27;
    php::Var tmp_var_28;
    php::Var tmp_var_29;
    zend_class_entry *tmp_var_4 = get_persistent_class(PersistentClassId{0}, get_str(1));
    Z_PTR_P(tmp_var_3.ptr()) = get_persistent_class(PersistentClassId{1}, get_str(26));

    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(16))}}, tmp_var_1)) {
        tmp_var_0 = tmp_var_1;
    } else {
        tmp_var_0 = php::Array{
        php::Var(0L), 
        php::Var(0L), 
        php::Var(0L), 
        php::Var(1L)
    };
    }
    tmp_var_2 = tmp_var_0;
    bg = php_pixelforge__color__parse(tmp_var_3, tmp_var_2);
    tmp_var_2.unset();
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(38))}}, tmp_var_6)) {
        tmp_var_5 = tmp_var_6;
    } else {
        tmp_var_5 = false;
    }
    tmp_var_7 = php::toBool(tmp_var_5);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(39))}}, tmp_var_9)) {
        tmp_var_8 = tmp_var_9;
    } else {
        tmp_var_8 = 1L;
    }
    tmp_var_10 = php::toInt(tmp_var_8);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(40))}}, tmp_var_12)) {
        tmp_var_11 = tmp_var_12;
    } else {
        tmp_var_11 = 0L;
    }
    tmp_var_13 = php::toInt(tmp_var_11);
    tmp_var_14 = bg.get(0L);
    tmp_var_15 = bg.get(1L);
    tmp_var_16 = bg.get(2L);
    tmp_var_17 = bg.get(3L);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(42))}}, tmp_var_19)) {
        tmp_var_18 = tmp_var_19;
    } else {
        tmp_var_18 = get_str(31);
    }
    tmp_var_20 = php::toString(tmp_var_18);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(43))}}, tmp_var_22)) {
        tmp_var_21 = tmp_var_22;
    } else {
        tmp_var_21 = get_str(44);
    }
    tmp_var_23 = php::toString(tmp_var_21);
    tmp_var_24 = php_pixelforge_join_new(php::toBool(tmp_var_7), php::toInt(tmp_var_10), php::toInt(tmp_var_13), php::toFloatArgExact(php::deindirect(tmp_var_14), get_str(41), 4, get_str(19)), php::toFloatArgExact(php::deindirect(tmp_var_15), get_str(41), 5, get_str(20)), php::toFloatArgExact(php::deindirect(tmp_var_16), get_str(41), 6, get_str(21)), php::toFloatArgExact(php::deindirect(tmp_var_17), get_str(41), 7, get_str(22)), tmp_var_20, tmp_var_23);
    tmp_var_14.unset();
    tmp_var_15.unset();
    tmp_var_16.unset();
    tmp_var_17.unset();
    tmp_var_20.unset();
    tmp_var_23.unset();
    img = php::newObject(tmp_var_4, php::VarList{tmp_var_24});
    tmp_var_24.unset();
    {
        php::ForeachIterator tmp_var_25{inputs, false, tmp_var_4};
        while (tmp_var_25.nextValue(in)) {
            tmp_var_26 = img.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
            tmp_var_27 = php_pixelforge__image__input(this_, in);
            tmp_var_28 = php_pixelforge__image__handle(tmp_var_27);
            tmp_var_27.unset();
            php_pixelforge_join_add(php::deindirect(tmp_var_26), (tmp_var_29 = tmp_var_28));
            tmp_var_26.unset();
            tmp_var_28.unset();
        }
    }
    return img;
}

php::Object php_pixelforge__image__input(php::Object &this_, php::Var in) {
    zend_function * tmp_var_0;
    php::Var tmp_var_1;
    php::Object tmp_var_2;
    php::Object tmp_var_3;
    php::Var tmp_var_4;
    php::Object tmp_var_5;
    php::Var tmp_var_6;
    php::Var tmp_var_7;
    php::Object tmp_var_8;
    php::Str s;
    zend_function * tmp_var_9;
    php::Var tmp_var_10;
    php::Bool tmp_var_11 = 0;
    zend_function * tmp_var_12;
    php::Bool tmp_var_13 = 0;
    zend_function * tmp_var_14;
    php::Object tmp_var_15;
    php::Object tmp_var_16;
    Z_PTR_P(tmp_var_2.ptr()) = get_persistent_class(PersistentClassId{0}, get_str(1));

    if (php::toBool(php::instanceOf(in, get_persistent_class(PersistentClassId{0}, get_str(1))))) {
        return php::toObject(in, get_persistent_class(PersistentClassId{0}, get_str(1)));
    }
    if (get_function_resolution_cache(FunctionResolutionCacheId{0}) == 0) { get_function_resolution_cache(FunctionResolutionCacheId{0}) = php::fn::function_exists(get_str(46)) ? 1 : 2; }
    tmp_var_0 = get_function_resolution_cache(FunctionResolutionCacheId{0}) == 1 ? get_func(RequestFuncId{0}, get_str(46)) : get_persistent_func(PersistentFuncId{0}, get_str(47));
    if (php::toBool(php::call(tmp_var_0, php::VarList{in}))) {
        if (php::toBool(php::exists(in, {{php::ArrayDimFetch, php::Var(get_str(48))}}))) {
            tmp_var_1 = in.item(get_str(48), false);
            tmp_var_3 = (php_pixelforge__image__create(tmp_var_2, php::deindirect(tmp_var_1)));
            tmp_var_1.unset();
            return tmp_var_3;
        }
        if (php::toBool(php::exists(in, {{php::ArrayDimFetch, php::Var(get_str(27))}}))) {
            tmp_var_4 = in.item(get_str(27), false);
            tmp_var_5 = (php_pixelforge__image__text(tmp_var_2, php::deindirect(tmp_var_4)));
            tmp_var_4.unset();
            return tmp_var_5;
        }
        if (php::toBool(php::exists(in, {{php::ArrayDimFetch, php::Var(get_str(9))}}))) {
            tmp_var_6 = php::toString(in.item(get_str(49), false));
            tmp_var_7 = in.item(get_str(9), false);
            tmp_var_8 = (php_pixelforge__image__fromraw(tmp_var_2, tmp_var_6, php::deindirect(tmp_var_7)));
            tmp_var_6.unset();
            tmp_var_7.unset();
            return tmp_var_8;
        }
    }
    s = php::toString(in);
    if (get_function_resolution_cache(FunctionResolutionCacheId{1}) == 0) { get_function_resolution_cache(FunctionResolutionCacheId{1}) = php::fn::function_exists(get_str(50)) ? 1 : 2; }
    tmp_var_9 = get_function_resolution_cache(FunctionResolutionCacheId{1}) == 1 ? get_func(RequestFuncId{1}, get_str(50)) : get_persistent_func(PersistentFuncId{1}, get_str(51));
    tmp_var_10 = php::call(tmp_var_9, php::VarList{s});
    tmp_var_11 = php::toBool(((php::Var(tmp_var_10)) < (php::Var(4096L))));
    tmp_var_10.unset();
    tmp_var_13 = php::toBool([&]() -> bool {
        if (php::toBool(tmp_var_11)) {
            if (get_function_resolution_cache(FunctionResolutionCacheId{2}) == 0) { get_function_resolution_cache(FunctionResolutionCacheId{2}) = php::fn::function_exists(get_str(52)) ? 1 : 2; }
            tmp_var_12 = get_function_resolution_cache(FunctionResolutionCacheId{2}) == 1 ? get_func(RequestFuncId{2}, get_str(52)) : get_persistent_func(PersistentFuncId{2}, get_str(53));
            return php::toBool(!(php::toBool(php::call(tmp_var_12, php::VarList{s, get_str(54)}))));
        }
        return false;
    }());
    if (php::toBool([&]() -> bool {
        if (php::toBool(tmp_var_13)) {
            if (get_function_resolution_cache(FunctionResolutionCacheId{3}) == 0) { get_function_resolution_cache(FunctionResolutionCacheId{3}) = php::fn::function_exists(get_str(55)) ? 1 : 2; }
            tmp_var_14 = get_function_resolution_cache(FunctionResolutionCacheId{3}) == 1 ? get_func(RequestFuncId{3}, get_str(55)) : get_persistent_func(PersistentFuncId{3}, get_str(56));
            return php::toBool(php::call(tmp_var_14, php::VarList{s}));
        }
        return false;
    }())) {
        tmp_var_15 = (php_pixelforge__image__fromfile(tmp_var_2, s));
        return tmp_var_15;
    }
    tmp_var_16 = (php_pixelforge__image__frombuffer(tmp_var_2, s));
    return tmp_var_16;
}

php::Int php_pixelforge__image__limit(php::Object &this_, php::Array options) {
    php::Var limit;
    php::Var tmp_var_0;
    php::Var tmp_var_1;
    php::Int tmp_var_2 = 0;

    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(57))}}, tmp_var_1)) {
        tmp_var_0 = tmp_var_1;
    } else {
        tmp_var_0 = 268402689L;
    }
    limit = tmp_var_0;
    if (php::toBool(php::same(limit, php::false_))) {
        return php::toInt(0L);
    }
    tmp_var_2 = (php::toInt(limit));
    return tmp_var_2;
}

php::Int php_pixelforge__image__pages(php::Object &this_, php::Array options) {
    php::Int tmp_var_0 = 0;
    php::Var tmp_var_1;
    php::Var tmp_var_2;
    php::Int tmp_var_3 = 0;

    if (php::toBool(!(php::toBool(php::empty(options, {{php::ArrayDimFetch, php::Var(get_str(38))}}))))) {
        tmp_var_0 = (php::toInt(-1L));
        return tmp_var_0;
    }
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(58))}}, tmp_var_2)) {
        tmp_var_1 = tmp_var_2;
    } else {
        tmp_var_1 = 1L;
    }
    tmp_var_3 = (php::toInt(tmp_var_1));
    return tmp_var_3;
}

php::Object php_pixelforge__image__clone(php::Object &this_) {
    php::Object img;
    php::Var tmp_var_1;
    php::Var tmp_var_2;
    zend_class_entry *tmp_var_0 = get_persistent_class(PersistentClassId{0}, get_str(1));
    php::Int &_object_prop_this___keepFlags = this_.attrInt(get_persistent_prop(PersistentPropertyId{1}, get_str(59), get_str(1)));

    tmp_var_1 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    tmp_var_2 = php_pixelforge_clone(php::deindirect(tmp_var_1));
    tmp_var_1.unset();
    img = php::newObject(tmp_var_0, php::VarList{tmp_var_2});
    tmp_var_2.unset();
    php::Int &_object_prop_img__keepFlags = Z_LVAL_P(img.attr(get_persistent_prop(PersistentPropertyId{1}, get_str(59), get_str(1)), php::AttrMode::Update).unwrap_ptr());
    _object_prop_img__keepFlags = _object_prop_this___keepFlags;
    return img;
}

php::Var php_pixelforge__image__handle(php::Object &this_) {
    php::Var tmp_var_0;

    tmp_var_0 = (this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get));
    return tmp_var_0;
}

php::Object php_pixelforge__image__resize(php::Object &this_, php::Var width, php::Var height, php::Array options) {
    php::Int w = 0;
    php::Int tmp_var_0 = 0;
    php::Var tmp_var_1;
    php::Var tmp_var_2;
    php::Int h = 0;
    php::Int tmp_var_3 = 0;
    php::Var tmp_var_4;
    php::Var tmp_var_5;
    php::Array bg;
    php::Var tmp_var_6;
    php::Var tmp_var_7;
    php::Var tmp_var_8;
    php::Object tmp_var_9;
    php::Var pos;
    php::Var tmp_var_10;
    php::Var tmp_var_11;
    php::Var tmp_var_12;
    php::Var tmp_var_13;
    php::Var tmp_var_14;
    php::Int tmp_var_15 = 0;
    php::Int tmp_var_16 = 0;
    php::Var tmp_var_17;
    php::Var tmp_var_18;
    php::Var tmp_var_19;
    php::Object tmp_var_20;
    php::Var tmp_var_21;
    php::Var tmp_var_22;
    php::Var tmp_var_23;
    php::Var tmp_var_24;
    php::Var tmp_var_25;
    php::Var tmp_var_26;
    php::Var tmp_var_27;
    php::Bool tmp_var_28 = 0;
    php::Var tmp_var_29;
    php::Var tmp_var_30;
    php::Bool tmp_var_31 = 0;
    php::Var tmp_var_32;
    php::Var tmp_var_33;
    php::Var tmp_var_34;
    php::Var tmp_var_35;
    php::Var tmp_var_36;
    php::Bool tmp_var_37 = 0;
    Z_PTR_P(tmp_var_9.ptr()) = get_persistent_class(PersistentClassId{1}, get_str(26));
    Z_PTR_P(tmp_var_20.ptr()) = get_persistent_class(PersistentClassId{2}, get_str(71));
    if (UNEXPECTED(!(width.isNull() || width.isInt()))) {
        php::throwArgumentTypeError(width, get_str(72), 1, get_str(10), get_str(73));
    }
    if (UNEXPECTED(!(height.isNull() || height.isInt()))) {
        php::throwArgumentTypeError(height, get_str(72), 2, get_str(11), get_str(73));
    }

    if (php::exists(width)) {
        tmp_var_0 = php::toInt(width);
    } else {
        if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(10))}}, tmp_var_2)) {
        tmp_var_1 = tmp_var_2;
    } else {
        tmp_var_1 = 0L;
    }
        tmp_var_0 = php::toInt(tmp_var_1);
    }
    w = php::toInt(tmp_var_0);
    if (php::exists(height)) {
        tmp_var_3 = php::toInt(height);
    } else {
        if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(11))}}, tmp_var_5)) {
        tmp_var_4 = tmp_var_5;
    } else {
        tmp_var_4 = 0L;
    }
        tmp_var_3 = php::toInt(tmp_var_4);
    }
    h = php::toInt(tmp_var_3);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(16))}}, tmp_var_7)) {
        tmp_var_6 = tmp_var_7;
    } else {
        tmp_var_6 = php::Array{
        php::Var(0L), 
        php::Var(0L), 
        php::Var(0L), 
        php::Var(1L)
    };
    }
    tmp_var_8 = tmp_var_6;
    bg = php_pixelforge__color__parse(tmp_var_9, tmp_var_8);
    tmp_var_8.unset();
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(60))}}, tmp_var_11)) {
        tmp_var_10 = tmp_var_11;
    } else {
        if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(61))}}, tmp_var_13)) {
        tmp_var_12 = tmp_var_13;
    } else {
        tmp_var_12 = get_str(62);
    }
        tmp_var_10 = tmp_var_12;
    }
    pos = tmp_var_10;
    tmp_var_14 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    tmp_var_15 = php::toInt(w);
    tmp_var_16 = php::toInt(h);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(63))}}, tmp_var_18)) {
        tmp_var_17 = tmp_var_18;
    } else {
        tmp_var_17 = get_str(64);
    }
    tmp_var_19 = php::toString(tmp_var_17);
    tmp_var_21 = php_pixelforge__gravity__normalise(tmp_var_20, php::toString(pos));
    tmp_var_22 = bg.get(0L);
    tmp_var_23 = bg.get(1L);
    tmp_var_24 = bg.get(2L);
    tmp_var_25 = bg.get(3L);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(66))}}, tmp_var_27)) {
        tmp_var_26 = tmp_var_27;
    } else {
        tmp_var_26 = false;
    }
    tmp_var_28 = php::toBool(tmp_var_26);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(67))}}, tmp_var_30)) {
        tmp_var_29 = tmp_var_30;
    } else {
        tmp_var_29 = false;
    }
    tmp_var_31 = php::toBool(tmp_var_29);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(68))}}, tmp_var_33)) {
        tmp_var_32 = tmp_var_33;
    } else {
        tmp_var_32 = get_str(69);
    }
    tmp_var_34 = php::toString(tmp_var_32);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(70))}}, tmp_var_36)) {
        tmp_var_35 = tmp_var_36;
    } else {
        tmp_var_35 = true;
    }
    tmp_var_37 = php::toBool(tmp_var_35);
    php_pixelforge_resize(php::deindirect(tmp_var_14), php::toInt(tmp_var_15), php::toInt(tmp_var_16), tmp_var_19, tmp_var_21, php::toFloatArgExact(php::deindirect(tmp_var_22), get_str(65), 6, get_str(19)), php::toFloatArgExact(php::deindirect(tmp_var_23), get_str(65), 7, get_str(20)), php::toFloatArgExact(php::deindirect(tmp_var_24), get_str(65), 8, get_str(21)), php::toFloatArgExact(php::deindirect(tmp_var_25), get_str(65), 9, get_str(22)), php::toBool(tmp_var_28), php::toBool(tmp_var_31), tmp_var_34, php::toBool(tmp_var_37));
    tmp_var_14.unset();
    tmp_var_19.unset();
    tmp_var_21.unset();
    tmp_var_22.unset();
    tmp_var_23.unset();
    tmp_var_24.unset();
    tmp_var_25.unset();
    tmp_var_34.unset();
    return this_;
}

php::Object php_pixelforge__image__extract(php::Object &this_, php::Array region) {
    php::Var tmp_var_0;
    php::Int tmp_var_1 = 0;
    php::Int tmp_var_2 = 0;
    php::Int tmp_var_3 = 0;
    php::Int tmp_var_4 = 0;

    tmp_var_0 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    tmp_var_1 = php::toInt(region.get(get_str(31)));
    tmp_var_2 = php::toInt(region.get(get_str(44)));
    tmp_var_3 = php::toInt(region.get(get_str(10)));
    tmp_var_4 = php::toInt(region.get(get_str(11)));
    php_pixelforge_extract(php::deindirect(tmp_var_0), php::toInt(tmp_var_1), php::toInt(tmp_var_2), php::toInt(tmp_var_3), php::toInt(tmp_var_4));
    tmp_var_0.unset();
    return this_;
}

php::Object php_pixelforge__image__extend(php::Object &this_, php::Var extend) {
    zend_function * tmp_var_0;
    php::Array bg;
    php::Var tmp_var_1;
    php::Var tmp_var_2;
    php::Var tmp_var_3;
    php::Object tmp_var_4;
    php::Var tmp_var_5;
    php::Var tmp_var_6;
    php::Var tmp_var_7;
    php::Int tmp_var_8 = 0;
    php::Var tmp_var_9;
    php::Var tmp_var_10;
    php::Int tmp_var_11 = 0;
    php::Var tmp_var_12;
    php::Var tmp_var_13;
    php::Int tmp_var_14 = 0;
    php::Var tmp_var_15;
    php::Var tmp_var_16;
    php::Int tmp_var_17 = 0;
    php::Var tmp_var_18;
    php::Var tmp_var_19;
    php::Var tmp_var_20;
    php::Var tmp_var_21;
    php::Var tmp_var_22;
    php::Var tmp_var_23;
    php::Var tmp_var_24;
    Z_PTR_P(tmp_var_4.ptr()) = get_persistent_class(PersistentClassId{1}, get_str(26));
    if (UNEXPECTED(!(extend.isInt() || extend.isArray()))) {
        php::throwArgumentTypeError(extend, get_str(80), 1, get_str(81), get_str(82));
    }

    if (get_function_resolution_cache(FunctionResolutionCacheId{4}) == 0) { get_function_resolution_cache(FunctionResolutionCacheId{4}) = php::fn::function_exists(get_str(74)) ? 1 : 2; }
    tmp_var_0 = get_function_resolution_cache(FunctionResolutionCacheId{4}) == 1 ? get_func(RequestFuncId{4}, get_str(74)) : get_persistent_func(PersistentFuncId{4}, get_str(75));
    if (php::toBool(php::call(tmp_var_0, php::VarList{extend}))) {
        extend = php::Array{
            { get_str(44).str(), php::Var(extend) }, 
            { get_str(76).str(), php::Var(extend) }, 
            { get_str(31).str(), php::Var(extend) }, 
            { get_str(77).str(), php::Var(extend) }
        };
    }
    if (php::exists(extend, {{php::ArrayDimFetch, php::Var(get_str(16))}}, tmp_var_2)) {
        tmp_var_1 = tmp_var_2;
    } else {
        tmp_var_1 = php::Array{
        php::Var(0L), 
        php::Var(0L), 
        php::Var(0L), 
        php::Var(1L)
    };
    }
    tmp_var_3 = tmp_var_1;
    bg = php_pixelforge__color__parse(tmp_var_4, tmp_var_3);
    tmp_var_3.unset();
    tmp_var_5 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    if (php::exists(extend, {{php::ArrayDimFetch, php::Var(get_str(44))}}, tmp_var_7)) {
        tmp_var_6 = tmp_var_7;
    } else {
        tmp_var_6 = 0L;
    }
    tmp_var_8 = php::toInt(tmp_var_6);
    if (php::exists(extend, {{php::ArrayDimFetch, php::Var(get_str(76))}}, tmp_var_10)) {
        tmp_var_9 = tmp_var_10;
    } else {
        tmp_var_9 = 0L;
    }
    tmp_var_11 = php::toInt(tmp_var_9);
    if (php::exists(extend, {{php::ArrayDimFetch, php::Var(get_str(31))}}, tmp_var_13)) {
        tmp_var_12 = tmp_var_13;
    } else {
        tmp_var_12 = 0L;
    }
    tmp_var_14 = php::toInt(tmp_var_12);
    if (php::exists(extend, {{php::ArrayDimFetch, php::Var(get_str(77))}}, tmp_var_16)) {
        tmp_var_15 = tmp_var_16;
    } else {
        tmp_var_15 = 0L;
    }
    tmp_var_17 = php::toInt(tmp_var_15);
    if (php::exists(extend, {{php::ArrayDimFetch, php::Var(get_str(78))}}, tmp_var_19)) {
        tmp_var_18 = tmp_var_19;
    } else {
        tmp_var_18 = get_str(16);
    }
    tmp_var_20 = php::toString(tmp_var_18);
    tmp_var_21 = bg.get(0L);
    tmp_var_22 = bg.get(1L);
    tmp_var_23 = bg.get(2L);
    tmp_var_24 = bg.get(3L);
    php_pixelforge_extend(php::deindirect(tmp_var_5), php::toInt(tmp_var_8), php::toInt(tmp_var_11), php::toInt(tmp_var_14), php::toInt(tmp_var_17), tmp_var_20, php::toFloatArgExact(php::deindirect(tmp_var_21), get_str(79), 7, get_str(19)), php::toFloatArgExact(php::deindirect(tmp_var_22), get_str(79), 8, get_str(20)), php::toFloatArgExact(php::deindirect(tmp_var_23), get_str(79), 9, get_str(21)), php::toFloatArgExact(php::deindirect(tmp_var_24), get_str(79), 10, get_str(22)));
    tmp_var_5.unset();
    tmp_var_20.unset();
    tmp_var_21.unset();
    tmp_var_22.unset();
    tmp_var_23.unset();
    tmp_var_24.unset();
    return this_;
}

php::Object php_pixelforge__image__trim(php::Object &this_, php::Array options) {
    php::Bool useBg = 0;
    php::Array bg;
    php::Var tmp_var_0;
    php::Var tmp_var_1;
    php::Var tmp_var_2;
    php::Object tmp_var_3;
    php::Var tmp_var_4;
    php::Var tmp_var_5;
    php::Var tmp_var_6;
    php::Float tmp_var_7 = 0;
    php::Bool tmp_var_8 = 0;
    php::Var tmp_var_9;
    php::Var tmp_var_10;
    php::Var tmp_var_11;
    php::Var tmp_var_12;
    php::Var tmp_var_13;
    php::Bool tmp_var_14 = 0;
    Z_PTR_P(tmp_var_3.ptr()) = get_persistent_class(PersistentClassId{1}, get_str(26));

    useBg = php::toBool(php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(16))}}));
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(16))}}, tmp_var_1)) {
        tmp_var_0 = tmp_var_1;
    } else {
        tmp_var_0 = php::Array{
        php::Var(0L), 
        php::Var(0L), 
        php::Var(0L), 
        php::Var(1L)
    };
    }
    tmp_var_2 = tmp_var_0;
    bg = php_pixelforge__color__parse(tmp_var_3, tmp_var_2);
    tmp_var_2.unset();
    tmp_var_4 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(83))}}, tmp_var_6)) {
        tmp_var_5 = tmp_var_6;
    } else {
        tmp_var_5 = 10L;
    }
    tmp_var_7 = php::toFloat(tmp_var_5);
    tmp_var_8 = php::toBool(useBg);
    tmp_var_9 = bg.get(0L);
    tmp_var_10 = bg.get(1L);
    tmp_var_11 = bg.get(2L);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(85))}}, tmp_var_13)) {
        tmp_var_12 = tmp_var_13;
    } else {
        tmp_var_12 = false;
    }
    tmp_var_14 = php::toBool(tmp_var_12);
    php_pixelforge_trim(php::deindirect(tmp_var_4), php::toFloat(tmp_var_7), php::toBool(tmp_var_8), php::toFloatArgExact(php::deindirect(tmp_var_9), get_str(84), 4, get_str(19)), php::toFloatArgExact(php::deindirect(tmp_var_10), get_str(84), 5, get_str(20)), php::toFloatArgExact(php::deindirect(tmp_var_11), get_str(84), 6, get_str(21)), php::toBool(tmp_var_14));
    tmp_var_4.unset();
    tmp_var_9.unset();
    tmp_var_10.unset();
    tmp_var_11.unset();
    return this_;
}

php::Object php_pixelforge__image__rotate(php::Object &this_, php::Var angle, php::Array options) {
    php::Object tmp_var_0;
    php::Array bg;
    php::Var tmp_var_1;
    php::Var tmp_var_2;
    php::Var tmp_var_3;
    php::Object tmp_var_4;
    php::Var tmp_var_5;
    php::Var tmp_var_6;
    php::Var tmp_var_7;
    php::Var tmp_var_8;
    php::Var tmp_var_9;
    php::Var tmp_var_10;
    Z_PTR_P(tmp_var_4.ptr()) = get_persistent_class(PersistentClassId{1}, get_str(26));
    if (angle.isInt()) {
        angle = php::toFloat(angle);
    }
    if (UNEXPECTED(!(angle.isNull() || angle.isFloat()))) {
        php::throwArgumentTypeError(angle, get_str(88), 1, get_str(87), get_str(89));
    }

    if (php::toBool(php::same(angle, php::null))) {
        tmp_var_0 = (php_pixelforge__image__autoorient(this_));
        return tmp_var_0;
    }
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(16))}}, tmp_var_2)) {
        tmp_var_1 = tmp_var_2;
    } else {
        tmp_var_1 = php::Array{
        php::Var(0L), 
        php::Var(0L), 
        php::Var(0L), 
        php::Var(1L)
    };
    }
    tmp_var_3 = tmp_var_1;
    bg = php_pixelforge__color__parse(tmp_var_4, tmp_var_3);
    tmp_var_3.unset();
    tmp_var_5 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    tmp_var_6 = angle;
    tmp_var_7 = bg.get(0L);
    tmp_var_8 = bg.get(1L);
    tmp_var_9 = bg.get(2L);
    tmp_var_10 = bg.get(3L);
    php_pixelforge_rotate(php::deindirect(tmp_var_5), php::toFloatArgExact(tmp_var_6, get_str(86), 2, get_str(87)), php::toFloatArgExact(php::deindirect(tmp_var_7), get_str(86), 3, get_str(19)), php::toFloatArgExact(php::deindirect(tmp_var_8), get_str(86), 4, get_str(20)), php::toFloatArgExact(php::deindirect(tmp_var_9), get_str(86), 5, get_str(21)), php::toFloatArgExact(php::deindirect(tmp_var_10), get_str(86), 6, get_str(22)));
    tmp_var_5.unset();
    tmp_var_6.unset();
    tmp_var_7.unset();
    tmp_var_8.unset();
    tmp_var_9.unset();
    tmp_var_10.unset();
    return this_;
}

php::Object php_pixelforge__image__autoorient(php::Object &this_) {
    php::Var tmp_var_0;

    tmp_var_0 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    php_pixelforge_auto_orient(php::deindirect(tmp_var_0));
    tmp_var_0.unset();
    return this_;
}

php::Object php_pixelforge__image__flip(php::Object &this_) {
    php::Var tmp_var_0;

    tmp_var_0 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    php_pixelforge_flip(php::deindirect(tmp_var_0));
    tmp_var_0.unset();
    return this_;
}

php::Object php_pixelforge__image__flop(php::Object &this_) {
    php::Var tmp_var_0;

    tmp_var_0 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    php_pixelforge_flop(php::deindirect(tmp_var_0));
    tmp_var_0.unset();
    return this_;
}

php::Object php_pixelforge__image__affine(php::Object &this_, php::Array matrix, php::Array options) {
    php::Array bg;
    php::Var tmp_var_0;
    php::Var tmp_var_1;
    php::Var tmp_var_2;
    php::Object tmp_var_3;
    php::Var tmp_var_4;
    php::Float tmp_var_5 = 0;
    php::Float tmp_var_6 = 0;
    php::Float tmp_var_7 = 0;
    php::Float tmp_var_8 = 0;
    php::Var tmp_var_9;
    php::Var tmp_var_10;
    php::Var tmp_var_11;
    php::Var tmp_var_12;
    php::Var tmp_var_13;
    php::Var tmp_var_14;
    php::Var tmp_var_15;
    php::Var tmp_var_16;
    php::Var tmp_var_17;
    php::Float tmp_var_18 = 0;
    php::Var tmp_var_19;
    php::Var tmp_var_20;
    php::Float tmp_var_21 = 0;
    php::Var tmp_var_22;
    php::Var tmp_var_23;
    php::Float tmp_var_24 = 0;
    php::Var tmp_var_25;
    php::Var tmp_var_26;
    php::Float tmp_var_27 = 0;
    Z_PTR_P(tmp_var_3.ptr()) = get_persistent_class(PersistentClassId{1}, get_str(26));

    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(16))}}, tmp_var_1)) {
        tmp_var_0 = tmp_var_1;
    } else {
        tmp_var_0 = php::Array{
        php::Var(0L), 
        php::Var(0L), 
        php::Var(0L), 
        php::Var(1L)
    };
    }
    tmp_var_2 = tmp_var_0;
    bg = php_pixelforge__color__parse(tmp_var_3, tmp_var_2);
    tmp_var_2.unset();
    tmp_var_4 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    tmp_var_5 = php::toFloat(matrix.get(0L));
    tmp_var_6 = php::toFloat(matrix.get(1L));
    tmp_var_7 = php::toFloat(matrix.get(2L));
    tmp_var_8 = php::toFloat(matrix.get(3L));
    tmp_var_9 = bg.get(0L);
    tmp_var_10 = bg.get(1L);
    tmp_var_11 = bg.get(2L);
    tmp_var_12 = bg.get(3L);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(93))}}, tmp_var_14)) {
        tmp_var_13 = tmp_var_14;
    } else {
        tmp_var_13 = get_str(94);
    }
    tmp_var_15 = php::toString(tmp_var_13);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(95))}}, tmp_var_17)) {
        tmp_var_16 = tmp_var_17;
    } else {
        tmp_var_16 = 0L;
    }
    tmp_var_18 = php::toFloat(tmp_var_16);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(96))}}, tmp_var_20)) {
        tmp_var_19 = tmp_var_20;
    } else {
        tmp_var_19 = 0L;
    }
    tmp_var_21 = php::toFloat(tmp_var_19);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(97))}}, tmp_var_23)) {
        tmp_var_22 = tmp_var_23;
    } else {
        tmp_var_22 = 0L;
    }
    tmp_var_24 = php::toFloat(tmp_var_22);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(98))}}, tmp_var_26)) {
        tmp_var_25 = tmp_var_26;
    } else {
        tmp_var_25 = 0L;
    }
    tmp_var_27 = php::toFloat(tmp_var_25);
    php_pixelforge_affine(php::deindirect(tmp_var_4), php::toFloat(tmp_var_5), php::toFloat(tmp_var_6), php::toFloat(tmp_var_7), php::toFloat(tmp_var_8), php::toFloatArgExact(php::deindirect(tmp_var_9), get_str(90), 6, get_str(19)), php::toFloatArgExact(php::deindirect(tmp_var_10), get_str(90), 7, get_str(20)), php::toFloatArgExact(php::deindirect(tmp_var_11), get_str(90), 8, get_str(91)), php::toFloatArgExact(php::deindirect(tmp_var_12), get_str(90), 9, get_str(92)), tmp_var_15, php::toFloat(tmp_var_18), php::toFloat(tmp_var_21), php::toFloat(tmp_var_24), php::toFloat(tmp_var_27));
    tmp_var_4.unset();
    tmp_var_9.unset();
    tmp_var_10.unset();
    tmp_var_11.unset();
    tmp_var_12.unset();
    tmp_var_15.unset();
    return this_;
}

php::Object php_pixelforge__image__sharpen(php::Object &this_, php::Array options) {
    php::Var tmp_var_0;
    php::Var tmp_var_1;
    php::Var tmp_var_2;
    php::Float tmp_var_3 = 0;
    php::Var tmp_var_4;
    php::Var tmp_var_5;
    php::Float tmp_var_6 = 0;
    php::Var tmp_var_7;
    php::Var tmp_var_8;
    php::Float tmp_var_9 = 0;
    php::Var tmp_var_10;
    php::Var tmp_var_11;
    php::Float tmp_var_12 = 0;
    php::Var tmp_var_13;
    php::Var tmp_var_14;
    php::Float tmp_var_15 = 0;
    php::Var tmp_var_16;
    php::Var tmp_var_17;
    php::Float tmp_var_18 = 0;

    tmp_var_0 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(25))}}, tmp_var_2)) {
        tmp_var_1 = tmp_var_2;
    } else {
        tmp_var_1 = 0L;
    }
    tmp_var_3 = php::toFloat(tmp_var_1);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(99))}}, tmp_var_5)) {
        tmp_var_4 = tmp_var_5;
    } else {
        tmp_var_4 = 1.0;
    }
    tmp_var_6 = php::toFloat(tmp_var_4);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(100))}}, tmp_var_8)) {
        tmp_var_7 = tmp_var_8;
    } else {
        tmp_var_7 = 2.0;
    }
    tmp_var_9 = php::toFloat(tmp_var_7);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(101))}}, tmp_var_11)) {
        tmp_var_10 = tmp_var_11;
    } else {
        tmp_var_10 = 2.0;
    }
    tmp_var_12 = php::toFloat(tmp_var_10);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(102))}}, tmp_var_14)) {
        tmp_var_13 = tmp_var_14;
    } else {
        tmp_var_13 = 10.0;
    }
    tmp_var_15 = php::toFloat(tmp_var_13);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(103))}}, tmp_var_17)) {
        tmp_var_16 = tmp_var_17;
    } else {
        tmp_var_16 = 20.0;
    }
    tmp_var_18 = php::toFloat(tmp_var_16);
    php_pixelforge_sharpen(php::deindirect(tmp_var_0), php::toFloat(tmp_var_3), php::toFloat(tmp_var_6), php::toFloat(tmp_var_9), php::toFloat(tmp_var_12), php::toFloat(tmp_var_15), php::toFloat(tmp_var_18));
    tmp_var_0.unset();
    return this_;
}

php::Object php_pixelforge__image__median(php::Object &this_, php::Int size) {
    php::Var tmp_var_0;

    tmp_var_0 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    php_pixelforge_median(php::deindirect(tmp_var_0), php::toInt(size));
    tmp_var_0.unset();
    return this_;
}

php::Object php_pixelforge__image__blur(php::Object &this_, php::Var sigma) {
    php::Var o;
    zend_function * tmp_var_0;
    php::Var tmp_var_1;
    php::Var tmp_var_2;
    php::Var tmp_var_3;
    php::Float tmp_var_4 = 0;
    php::Var tmp_var_5;
    php::Var tmp_var_6;
    php::Var tmp_var_7;
    php::Var tmp_var_8;
    php::Var tmp_var_9;
    php::Float tmp_var_10 = 0;
    if (sigma.isInt()) {
        sigma = php::toFloat(sigma);
    }
    if (UNEXPECTED(!(sigma.isFloat() || sigma.isArray()))) {
        php::throwArgumentTypeError(sigma, get_str(107), 1, get_str(25), get_str(108));
    }

    o = [&]() -> php::Var {
        if (get_function_resolution_cache(FunctionResolutionCacheId{5}) == 0) { get_function_resolution_cache(FunctionResolutionCacheId{5}) = php::fn::function_exists(get_str(46)) ? 1 : 2; }
        tmp_var_0 = get_function_resolution_cache(FunctionResolutionCacheId{5}) == 1 ? get_func(RequestFuncId{0}, get_str(46)) : get_persistent_func(PersistentFuncId{0}, get_str(47));
        if (php::toBool(php::call(tmp_var_0, php::VarList{sigma}))) {
            return php::Var(sigma);
        } else {
            return php::Var(php::Array{
        { get_str(25).str(), php::Var(sigma) }
    });
        }
    }();
    tmp_var_1 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(25))}}, tmp_var_3)) {
        tmp_var_2 = tmp_var_3;
    } else {
        tmp_var_2 = 0L;
    }
    tmp_var_4 = php::toFloat(tmp_var_2);
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(104))}}, tmp_var_6)) {
        tmp_var_5 = tmp_var_6;
    } else {
        tmp_var_5 = get_str(105);
    }
    tmp_var_7 = php::toString(tmp_var_5);
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(106))}}, tmp_var_9)) {
        tmp_var_8 = tmp_var_9;
    } else {
        tmp_var_8 = 0.20000000000000001;
    }
    tmp_var_10 = php::toFloat(tmp_var_8);
    php_pixelforge_blur(php::deindirect(tmp_var_1), php::toFloat(tmp_var_4), tmp_var_7, php::toFloat(tmp_var_10));
    tmp_var_1.unset();
    tmp_var_7.unset();
    return this_;
}

php::Object php_pixelforge__image__flatten(php::Object &this_, php::Array options) {
    php::Array bg;
    php::Var tmp_var_0;
    php::Var tmp_var_1;
    php::Var tmp_var_2;
    php::Object tmp_var_3;
    php::Var tmp_var_4;
    php::Var tmp_var_5;
    php::Var tmp_var_6;
    php::Var tmp_var_7;
    Z_PTR_P(tmp_var_3.ptr()) = get_persistent_class(PersistentClassId{1}, get_str(26));

    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(16))}}, tmp_var_1)) {
        tmp_var_0 = tmp_var_1;
    } else {
        tmp_var_0 = php::Array{
        php::Var(0L), 
        php::Var(0L), 
        php::Var(0L), 
        php::Var(1L)
    };
    }
    tmp_var_2 = tmp_var_0;
    bg = php_pixelforge__color__parse(tmp_var_3, tmp_var_2);
    tmp_var_2.unset();
    tmp_var_4 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    tmp_var_5 = bg.get(0L);
    tmp_var_6 = bg.get(1L);
    tmp_var_7 = bg.get(2L);
    php_pixelforge_flatten(php::deindirect(tmp_var_4), php::toFloatArgExact(php::deindirect(tmp_var_5), get_str(109), 2, get_str(19)), php::toFloatArgExact(php::deindirect(tmp_var_6), get_str(109), 3, get_str(20)), php::toFloatArgExact(php::deindirect(tmp_var_7), get_str(109), 4, get_str(21)));
    tmp_var_4.unset();
    tmp_var_5.unset();
    tmp_var_6.unset();
    tmp_var_7.unset();
    return this_;
}

php::Object php_pixelforge__image__unflatten(php::Object &this_) {
    php::Var tmp_var_0;

    tmp_var_0 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    php_pixelforge_unflatten(php::deindirect(tmp_var_0));
    tmp_var_0.unset();
    return this_;
}

php::Object php_pixelforge__image__gamma(php::Object &this_, php::Float gamma, php::Var gammaOut) {
    php::Var tmp_var_0;
    php::Float tmp_var_1 = 0;
    if (gammaOut.isInt()) {
        gammaOut = php::toFloat(gammaOut);
    }
    if (UNEXPECTED(!(gammaOut.isNull() || gammaOut.isFloat()))) {
        php::throwArgumentTypeError(gammaOut, get_str(110), 2, get_str(111), get_str(89));
    }

    tmp_var_0 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    if (php::exists(gammaOut)) {
        tmp_var_1 = php::toFloat(gammaOut);
    } else {
        tmp_var_1 = php::toFloat(gamma);
    }
    php_pixelforge_gamma(php::deindirect(tmp_var_0), php::toFloat(gamma), php::toFloat(tmp_var_1));
    tmp_var_0.unset();
    return this_;
}

php::Object php_pixelforge__image__negate(php::Object &this_, php::Array options) {
    php::Var tmp_var_0;
    php::Var tmp_var_1;
    php::Var tmp_var_2;
    php::Bool tmp_var_3 = 0;

    tmp_var_0 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(112))}}, tmp_var_2)) {
        tmp_var_1 = tmp_var_2;
    } else {
        tmp_var_1 = true;
    }
    tmp_var_3 = php::toBool(tmp_var_1);
    php_pixelforge_negate(php::deindirect(tmp_var_0), php::toBool(tmp_var_3));
    tmp_var_0.unset();
    return this_;
}

php::Object php_pixelforge__image__normalise(php::Object &this_, php::Array options) {
    php::Var tmp_var_0;
    php::Var tmp_var_1;
    php::Var tmp_var_2;
    php::Float tmp_var_3 = 0;
    php::Var tmp_var_4;
    php::Var tmp_var_5;
    php::Float tmp_var_6 = 0;

    tmp_var_0 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(113))}}, tmp_var_2)) {
        tmp_var_1 = tmp_var_2;
    } else {
        tmp_var_1 = 1L;
    }
    tmp_var_3 = php::toFloat(tmp_var_1);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(114))}}, tmp_var_5)) {
        tmp_var_4 = tmp_var_5;
    } else {
        tmp_var_4 = 99L;
    }
    tmp_var_6 = php::toFloat(tmp_var_4);
    php_pixelforge_normalise(php::deindirect(tmp_var_0), php::toFloat(tmp_var_3), php::toFloat(tmp_var_6));
    tmp_var_0.unset();
    return this_;
}

php::Object php_pixelforge__image__normalize(php::Object &this_, php::Array options) {
    php::Object tmp_var_0;

    tmp_var_0 = (php_pixelforge__image__normalise(this_, options));
    return tmp_var_0;
}

php::Object php_pixelforge__image__clahe(php::Object &this_, php::Array options) {
    php::Var tmp_var_0;
    php::Int tmp_var_1 = 0;
    php::Int tmp_var_2 = 0;
    php::Var tmp_var_3;
    php::Var tmp_var_4;
    php::Int tmp_var_5 = 0;

    tmp_var_0 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    tmp_var_1 = php::toInt(options.get(get_str(10)));
    tmp_var_2 = php::toInt(options.get(get_str(11)));
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(116))}}, tmp_var_4)) {
        tmp_var_3 = tmp_var_4;
    } else {
        tmp_var_3 = 3L;
    }
    tmp_var_5 = php::toInt(tmp_var_3);
    php_pixelforge_clahe(php::deindirect(tmp_var_0), php::toInt(tmp_var_1), php::toInt(tmp_var_2), php::toInt(tmp_var_5));
    tmp_var_0.unset();
    return this_;
}

php::Object php_pixelforge__image__threshold(php::Object &this_, php::Int threshold, php::Array options) {
    php::Bool grey = 0;
    php::Var tmp_var_0;
    php::Var tmp_var_1;
    php::Var tmp_var_2;
    php::Var tmp_var_3;
    php::Var tmp_var_4;

    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(117))}}, tmp_var_1)) {
        tmp_var_0 = tmp_var_1;
    } else {
        if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(118))}}, tmp_var_3)) {
        tmp_var_2 = tmp_var_3;
    } else {
        tmp_var_2 = true;
    }
        tmp_var_0 = tmp_var_2;
    }
    grey = php::toBool(tmp_var_0);
    tmp_var_4 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    php_pixelforge_threshold(php::deindirect(tmp_var_4), php::toInt(threshold), php::toBool(grey));
    tmp_var_4.unset();
    return this_;
}

php::Object php_pixelforge__image__linear(php::Object &this_, php::Var a, php::Var b) {
    php::Var tmp_var_0;
    php::Var tmp_var_1;
    php::Var tmp_var_2;
    if (a.isInt()) {
        a = php::toFloat(a);
    }
    if (UNEXPECTED(!(a.isFloat() || a.isArray()))) {
        php::throwArgumentTypeError(a, get_str(119), 1, get_str(22), get_str(108));
    }
    if (b.isInt()) {
        b = php::toFloat(b);
    }
    if (UNEXPECTED(!(b.isFloat() || b.isArray()))) {
        php::throwArgumentTypeError(b, get_str(119), 2, get_str(21), get_str(108));
    }

    tmp_var_0 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    tmp_var_1 = php_pixelforge__image__csv(this_, a);
    tmp_var_2 = php_pixelforge__image__csv(this_, b);
    php_pixelforge_linear(php::deindirect(tmp_var_0), tmp_var_1, tmp_var_2);
    tmp_var_0.unset();
    tmp_var_1.unset();
    tmp_var_2.unset();
    return this_;
}

php::Object php_pixelforge__image__modulate(php::Object &this_, php::Array options) {
    php::Var tmp_var_0;
    php::Var tmp_var_1;
    php::Var tmp_var_2;
    php::Float tmp_var_3 = 0;
    php::Var tmp_var_4;
    php::Var tmp_var_5;
    php::Float tmp_var_6 = 0;
    php::Var tmp_var_7;
    php::Var tmp_var_8;
    php::Float tmp_var_9 = 0;
    php::Var tmp_var_10;
    php::Var tmp_var_11;
    php::Float tmp_var_12 = 0;

    tmp_var_0 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(120))}}, tmp_var_2)) {
        tmp_var_1 = tmp_var_2;
    } else {
        tmp_var_1 = 1L;
    }
    tmp_var_3 = php::toFloat(tmp_var_1);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(121))}}, tmp_var_5)) {
        tmp_var_4 = tmp_var_5;
    } else {
        tmp_var_4 = 1L;
    }
    tmp_var_6 = php::toFloat(tmp_var_4);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(122))}}, tmp_var_8)) {
        tmp_var_7 = tmp_var_8;
    } else {
        tmp_var_7 = 0L;
    }
    tmp_var_9 = php::toFloat(tmp_var_7);
    if (php::exists(options, {{php::ArrayDimFetch, php::Var(get_str(123))}}, tmp_var_11)) {
        tmp_var_10 = tmp_var_11;
    } else {
        tmp_var_10 = 0L;
    }
    tmp_var_12 = php::toFloat(tmp_var_10);
    php_pixelforge_modulate(php::deindirect(tmp_var_0), php::toFloat(tmp_var_3), php::toFloat(tmp_var_6), php::toFloat(tmp_var_9), php::toFloat(tmp_var_12));
    tmp_var_0.unset();
    return this_;
}

php::Object php_pixelforge__image__tint(php::Object &this_, php::Var color) {
    php::Array c;
    php::Object tmp_var_0;
    php::Var tmp_var_1;
    php::Var tmp_var_2;
    php::Var tmp_var_3;
    php::Var tmp_var_4;
    Z_PTR_P(tmp_var_0.ptr()) = get_persistent_class(PersistentClassId{1}, get_str(26));

    c = php_pixelforge__color__parse(tmp_var_0, color);
    tmp_var_1 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    tmp_var_2 = c.get(0L);
    tmp_var_3 = c.get(1L);
    tmp_var_4 = c.get(2L);
    php_pixelforge_tint(php::deindirect(tmp_var_1), php::toFloatArgExact(php::deindirect(tmp_var_2), get_str(124), 2, get_str(19)), php::toFloatArgExact(php::deindirect(tmp_var_3), get_str(124), 3, get_str(20)), php::toFloatArgExact(php::deindirect(tmp_var_4), get_str(124), 4, get_str(21)));
    tmp_var_1.unset();
    tmp_var_2.unset();
    tmp_var_3.unset();
    tmp_var_4.unset();
    return this_;
}

php::Object php_pixelforge__image__greyscale(php::Object &this_, php::Bool grey) {
    php::Var tmp_var_0;

    if (php::toBool(grey)) {
        tmp_var_0 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
        php_pixelforge_colourspace(php::deindirect(tmp_var_0), get_str(125));
        tmp_var_0.unset();
    }
    return this_;
}

php::Object php_pixelforge__image__grayscale(php::Object &this_, php::Bool grey) {
    php::Object tmp_var_0;

    tmp_var_0 = (php_pixelforge__image__greyscale(this_, php::toBool(grey)));
    return tmp_var_0;
}

php::Object php_pixelforge__image__tocolourspace(php::Object &this_, php::Str space) {
    php::Var tmp_var_0;

    tmp_var_0 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    php_pixelforge_colourspace(php::deindirect(tmp_var_0), space);
    tmp_var_0.unset();
    return this_;
}

php::Object php_pixelforge__image__tocolorspace(php::Object &this_, php::Str space) {
    php::Object tmp_var_0;

    tmp_var_0 = (php_pixelforge__image__tocolourspace(this_, space));
    return tmp_var_0;
}

php::Object php_pixelforge__image__removealpha(php::Object &this_) {
    php::Var tmp_var_0;

    tmp_var_0 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    php_pixelforge_remove_alpha(php::deindirect(tmp_var_0));
    tmp_var_0.unset();
    return this_;
}

php::Object php_pixelforge__image__ensurealpha(php::Object &this_, php::Float alpha) {
    php::Var tmp_var_0;

    tmp_var_0 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    php_pixelforge_ensure_alpha(php::deindirect(tmp_var_0), php::toFloat(alpha));
    tmp_var_0.unset();
    return this_;
}

php::Object php_pixelforge__image__extractchannel(php::Object &this_, php::Var channel) {
    zend_function * tmp_var_0;
    php::Array map;
    php::Var tmp_var_2;
    zend_class_entry *tmp_var_1 = get_persistent_class(PersistentClassId{3}, get_str(135));
    if (UNEXPECTED(!(channel.isInt() || channel.isString()))) {
        php::throwArgumentTypeError(channel, get_str(136), 1, get_str(134), get_str(137));
    }

    if (get_function_resolution_cache(FunctionResolutionCacheId{6}) == 0) { get_function_resolution_cache(FunctionResolutionCacheId{6}) = php::fn::function_exists(get_str(127)) ? 1 : 2; }
    tmp_var_0 = get_function_resolution_cache(FunctionResolutionCacheId{6}) == 1 ? get_func(RequestFuncId{5}, get_str(127)) : get_persistent_func(PersistentFuncId{5}, get_str(128));
    if (php::toBool(php::call(tmp_var_0, php::VarList{channel}))) {
        map = php::Array{
            { get_str(129).str(), php::Var(0L) }, 
            { get_str(130).str(), php::Var(1L) }, 
            { get_str(131).str(), php::Var(2L) }, 
            { get_str(112).str(), php::Var(3L) }
        };
        if (php::toBool(!(php::toBool(php::exists(map, {{php::ArrayDimFetch, php::Var(channel)}}))))) {
            php::throwException(php::newObject(tmp_var_1, php::VarList{php::concat({get_str(132), php::toString(channel)})}));
        }
        channel = map.item(channel, false);
    }
    tmp_var_2 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    php_pixelforge_extract_channel(php::deindirect(tmp_var_2), php::toIntArgExact(channel, get_str(133), 2, get_str(134)));
    tmp_var_2.unset();
    return this_;
}

php::Object php_pixelforge__image__joinchannel(php::Object &this_, php::Var images) {
    php::Var list;
    zend_function * tmp_var_0;
    php::Var tmp_var_1;
    php::Bool tmp_var_2 = 0;
    php::Var tmp_var_3;
    php::Var img;
    php::Var tmp_var_6;
    php::Object tmp_var_7;
    php::Var tmp_var_8;
    php::Var tmp_var_9;
    zend_class_entry *tmp_var_5 = get_persistent_class(PersistentClassId{0}, get_str(1));

    list = [&]() -> php::Var {
        if (get_function_resolution_cache(FunctionResolutionCacheId{7}) == 0) { get_function_resolution_cache(FunctionResolutionCacheId{7}) = php::fn::function_exists(get_str(46)) ? 1 : 2; }
        tmp_var_0 = get_function_resolution_cache(FunctionResolutionCacheId{7}) == 1 ? get_func(RequestFuncId{0}, get_str(46)) : get_persistent_func(PersistentFuncId{0}, get_str(47));
        tmp_var_1 = php::call(tmp_var_0, php::VarList{images});
        tmp_var_2 = php::toBool((php::toBool(tmp_var_1) && php::toBool(!(php::toBool(php::exists(images, {{php::ArrayDimFetch, php::Var(get_str(48))}}))))));
        tmp_var_1.unset();
        if (php::toBool((php::toBool(tmp_var_2) && php::toBool(!(php::toBool(php::exists(images, {{php::ArrayDimFetch, php::Var(get_str(27))}}))))))) {
            return php::Var(images);
        } else {
            return php::Var(php::Array{
        php::Var(images)
    });
        }
    }();

    tmp_var_3 = list;
    {
        php::ForeachIterator tmp_var_4{tmp_var_3, false, tmp_var_5};
        while (tmp_var_4.next()) {
            img = tmp_var_4.value();
            tmp_var_6 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
            tmp_var_7 = php_pixelforge__image__input(this_, img);
            tmp_var_8 = php_pixelforge__image__handle(tmp_var_7);
            tmp_var_7.unset();
            php_pixelforge_join_channel(php::deindirect(tmp_var_6), (tmp_var_9 = tmp_var_8));
            tmp_var_6.unset();
            tmp_var_8.unset();
        }
    }
    return this_;
}

php::Object php_pixelforge__image__bandbool(php::Object &this_, php::Str op) {
    php::Var tmp_var_0;

    tmp_var_0 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    php_pixelforge_bandbool(php::deindirect(tmp_var_0), op);
    tmp_var_0.unset();
    return this_;
}

php::Object php_pixelforge__image__boolean(php::Object &this_, php::Var operand, php::Str op) {
    php::Var tmp_var_0;
    php::Object tmp_var_1;
    php::Var tmp_var_2;
    php::Var tmp_var_3;

    tmp_var_0 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    tmp_var_1 = php_pixelforge__image__input(this_, operand);
    tmp_var_2 = php_pixelforge__image__handle(tmp_var_1);
    tmp_var_1.unset();
    php_pixelforge_boolean(php::deindirect(tmp_var_0), (tmp_var_3 = tmp_var_2), op);
    tmp_var_0.unset();
    tmp_var_2.unset();
    return this_;
}

php::Object php_pixelforge__image__dilate(php::Object &this_, php::Int width) {
    php::Var tmp_var_0;

    tmp_var_0 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    php_pixelforge_dilate(php::deindirect(tmp_var_0), php::toInt(width));
    tmp_var_0.unset();
    return this_;
}

php::Object php_pixelforge__image__erode(php::Object &this_, php::Int width) {
    php::Var tmp_var_0;

    tmp_var_0 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    php_pixelforge_erode(php::deindirect(tmp_var_0), php::toInt(width));
    tmp_var_0.unset();
    return this_;
}

php::Object php_pixelforge__image__convolve(php::Object &this_, php::Array kernel) {
    php::Var tmp_var_0;
    php::Int tmp_var_1 = 0;
    php::Int tmp_var_2 = 0;
    php::Var tmp_var_3;
    php::Var tmp_var_4;
    php::Var tmp_var_5;
    php::Var tmp_var_6;
    php::Float tmp_var_7 = 0;
    php::Var tmp_var_8;
    php::Var tmp_var_9;
    php::Float tmp_var_10 = 0;

    tmp_var_0 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    tmp_var_1 = php::toInt(kernel.get(get_str(10)));
    tmp_var_2 = php::toInt(kernel.get(get_str(11)));
    tmp_var_3 = kernel.get(get_str(68));
    tmp_var_4 = php_pixelforge__image__csv(this_, php::deindirect(tmp_var_3));
    tmp_var_3.unset();
    if (php::exists(kernel, {{php::ArrayDimFetch, php::Var(get_str(138))}}, tmp_var_6)) {
        tmp_var_5 = tmp_var_6;
    } else {
        tmp_var_5 = 0L;
    }
    tmp_var_7 = php::toFloat(tmp_var_5);
    if (php::exists(kernel, {{php::ArrayDimFetch, php::Var(get_str(139))}}, tmp_var_9)) {
        tmp_var_8 = tmp_var_9;
    } else {
        tmp_var_8 = 0L;
    }
    tmp_var_10 = php::toFloat(tmp_var_8);
    php_pixelforge_convolve(php::deindirect(tmp_var_0), php::toInt(tmp_var_1), php::toInt(tmp_var_2), tmp_var_4, php::toFloat(tmp_var_7), php::toFloat(tmp_var_10));
    tmp_var_0.unset();
    tmp_var_4.unset();
    return this_;
}

php::Object php_pixelforge__image__recomb(php::Object &this_, php::Array matrix) {
    php::Array flat;
    php::Var row;
    php::Var tmp_var_2;
    php::Var v;
    php::Var tmp_var_4;
    php::Var tmp_var_5;
    zend_class_entry *tmp_var_1 = get_persistent_class(PersistentClassId{0}, get_str(1));

    flat = php::Array{};
    {
        php::ForeachIterator tmp_var_0{matrix, false, tmp_var_1};
        while (tmp_var_0.nextValue(row)) {

            tmp_var_2 = row;
            {
                php::ForeachIterator tmp_var_3{tmp_var_2, false, tmp_var_1};
                while (tmp_var_3.next()) {
                    v = tmp_var_3.value();
                    flat.appendValue(php::toFloat(v));
                }
            }
        }
    }
    tmp_var_4 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    tmp_var_5 = php_pixelforge__image__csv(this_, flat);
    php_pixelforge_recomb(php::deindirect(tmp_var_4), tmp_var_5);
    tmp_var_4.unset();
    tmp_var_5.unset();
    return this_;
}

php::Object php_pixelforge__image__composite(php::Object &this_, php::Array layers) {
    php::Var layer;
    php::Object input;
    php::Var tmp_var_2;
    php::Bool hasPos = 0;
    php::Bool tmp_var_3 = 0;
    php::Var tmp_var_4;
    php::Var tmp_var_5;
    php::Var tmp_var_6;
    php::Var tmp_var_7;
    php::Var tmp_var_8;
    php::Object tmp_var_9;
    php::Var tmp_var_10;
    php::Int tmp_var_11 = 0;
    php::Int tmp_var_12 = 0;
    php::Var tmp_var_13;
    php::Var tmp_var_14;
    php::Var tmp_var_15;
    php::Var tmp_var_16;
    php::Var tmp_var_17;
    php::Bool tmp_var_18 = 0;
    php::Var tmp_var_19;
    php::Var tmp_var_20;
    php::Bool tmp_var_21 = 0;
    zend_class_entry *tmp_var_1 = get_persistent_class(PersistentClassId{0}, get_str(1));
    Z_PTR_P(tmp_var_9.ptr()) = get_persistent_class(PersistentClassId{2}, get_str(71));

    {
        php::ForeachIterator tmp_var_0{layers, false, tmp_var_1};
        while (tmp_var_0.nextValue(layer)) {
            tmp_var_2 = layer.item(get_str(49), false);
            input = php_pixelforge__image__input(this_, php::deindirect(tmp_var_2));
            tmp_var_2.unset();
            tmp_var_3 = php::toBool(php::exists(layer, {{php::ArrayDimFetch, php::Var(get_str(31))}}));
            hasPos = php::toBool((php::toBool(tmp_var_3) && php::toBool(php::exists(layer, {{php::ArrayDimFetch, php::Var(get_str(44))}}))));
            tmp_var_4 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
            tmp_var_5 = php_pixelforge__image__handle(input);
            if (php::exists(layer, {{php::ArrayDimFetch, php::Var(get_str(61))}}, tmp_var_7)) {
                tmp_var_6 = tmp_var_7;
            } else {
                tmp_var_6 = get_str(62);
            }
            tmp_var_8 = php::toString(tmp_var_6);
            tmp_var_10 = php_pixelforge__gravity__normalise(tmp_var_9, tmp_var_8);
            tmp_var_8.unset();
            tmp_var_11 = php::toInt((php::toBool(hasPos)) ? (php::toInt(layer.item(get_str(31), false))) : (-2147483648L));
            tmp_var_12 = php::toInt((php::toBool(hasPos)) ? (php::toInt(layer.item(get_str(44), false))) : (-2147483648L));
            if (php::exists(layer, {{php::ArrayDimFetch, php::Var(get_str(140))}}, tmp_var_14)) {
                tmp_var_13 = tmp_var_14;
            } else {
                tmp_var_13 = get_str(141);
            }
            tmp_var_15 = php::toString(tmp_var_13);
            if (php::exists(layer, {{php::ArrayDimFetch, php::Var(get_str(142))}}, tmp_var_17)) {
                tmp_var_16 = tmp_var_17;
            } else {
                tmp_var_16 = false;
            }
            tmp_var_18 = php::toBool(tmp_var_16);
            if (php::exists(layer, {{php::ArrayDimFetch, php::Var(get_str(15))}}, tmp_var_20)) {
                tmp_var_19 = tmp_var_20;
            } else {
                tmp_var_19 = false;
            }
            tmp_var_21 = php::toBool(tmp_var_19);
            php_pixelforge_composite(php::deindirect(tmp_var_4), tmp_var_5, tmp_var_10, php::toInt(tmp_var_11), php::toInt(tmp_var_12), tmp_var_15, php::toBool(tmp_var_18), php::toBool(tmp_var_21));
            tmp_var_4.unset();
            tmp_var_5.unset();
            tmp_var_10.unset();
            tmp_var_15.unset();
        }
    }
    return this_;
}

php::Object php_pixelforge__image__jpeg(php::Object &this_, php::Array o) {
    php::Object tmp_var_0;

    tmp_var_0 = (php_pixelforge__image__output(this_, get_str(144), o));
    return tmp_var_0;
}

php::Object php_pixelforge__image__png(php::Object &this_, php::Array o) {
    php::Object tmp_var_0;

    tmp_var_0 = (php_pixelforge__image__output(this_, get_str(145), o));
    return tmp_var_0;
}

php::Object php_pixelforge__image__webp(php::Object &this_, php::Array o) {
    php::Object tmp_var_0;

    tmp_var_0 = (php_pixelforge__image__output(this_, get_str(146), o));
    return tmp_var_0;
}

php::Object php_pixelforge__image__avif(php::Object &this_, php::Array o) {
    php::Object tmp_var_0;

    tmp_var_0 = (php_pixelforge__image__output(this_, get_str(147), o));
    return tmp_var_0;
}

php::Object php_pixelforge__image__heif(php::Object &this_, php::Array o) {
    php::Object tmp_var_0;

    tmp_var_0 = (php_pixelforge__image__output(this_, get_str(148), o));
    return tmp_var_0;
}

php::Object php_pixelforge__image__gif(php::Object &this_, php::Array o) {
    php::Object tmp_var_0;

    tmp_var_0 = (php_pixelforge__image__output(this_, get_str(149), o));
    return tmp_var_0;
}

php::Object php_pixelforge__image__tiff(php::Object &this_, php::Array o) {
    php::Object tmp_var_0;

    tmp_var_0 = (php_pixelforge__image__output(this_, get_str(150), o));
    return tmp_var_0;
}

php::Object php_pixelforge__image__jxl(php::Object &this_, php::Array o) {
    php::Object tmp_var_0;

    tmp_var_0 = (php_pixelforge__image__output(this_, get_str(151), o));
    return tmp_var_0;
}

php::Object php_pixelforge__image__raw(php::Object &this_) {
    php::Var tmp_var_0;
    php::Object tmp_var_1;

    tmp_var_0 = php::Array{};
    tmp_var_1 = (php_pixelforge__image__output(this_, get_str(9), tmp_var_0));
    tmp_var_0.unset();
    return tmp_var_1;
}

php::Object php_pixelforge__image__toformat(php::Object &this_, php::Str format, php::Array o) {
    php::Object tmp_var_0;

    tmp_var_0 = (php_pixelforge__image__output(this_, format, o));
    return tmp_var_0;
}

php::Object php_pixelforge__image__output(php::Object &this_, php::Str format, php::Array o) {
    php::Var tmp_var_0;
    php::Str tmp_var_1;
    php::Var tmp_var_2;
    php::Var tmp_var_3;
    php::Int tmp_var_4 = 0;
    php::Var tmp_var_5;
    php::Var tmp_var_6;
    php::Bool tmp_var_7 = 0;
    php::Var tmp_var_8;
    php::Var tmp_var_9;
    php::Int tmp_var_10 = 0;
    php::Var tmp_var_11;
    php::Var tmp_var_12;
    php::Var tmp_var_13;
    php::Var tmp_var_14;
    php::Bool tmp_var_15 = 0;
    php::Var tmp_var_16;
    php::Var tmp_var_17;
    php::Var tmp_var_18;
    php::Var tmp_var_19;
    php::Var tmp_var_20;
    php::Bool tmp_var_21 = 0;
    php::Var tmp_var_22;
    php::Var tmp_var_23;
    php::Int tmp_var_24 = 0;
    php::Var tmp_var_25;
    php::Var tmp_var_26;
    php::Bool tmp_var_27 = 0;
    php::Bool tmp_var_28 = 0;
    php::Var tmp_var_29;
    php::Var tmp_var_30;
    php::Var tmp_var_31;
    php::Var tmp_var_32;
    php::Int tmp_var_33 = 0;
    php::Var tmp_var_34;
    php::Var tmp_var_35;
    php::Float tmp_var_36 = 0;
    php::Var tmp_var_37;
    php::Var tmp_var_38;
    php::Bool tmp_var_39 = 0;
    php::Var tmp_var_40;
    php::Var tmp_var_41;
    php::Int tmp_var_42 = 0;
    php::Var tmp_var_43;
    php::Var tmp_var_44;
    php::Bool tmp_var_45 = 0;
    php::Var tmp_var_46;
    php::Var tmp_var_47;
    php::Int tmp_var_48 = 0;
    php::Var tmp_var_49;
    php::Var tmp_var_50;
    php::Int tmp_var_51 = 0;
    php::Var tmp_var_52;
    php::Var tmp_var_53;
    php::Var tmp_var_54;
    php::Var tmp_var_55;
    php::Var tmp_var_56;
    php::Var tmp_var_57;
    php::Var tmp_var_58;
    php::Var tmp_var_59;
    php::Bool tmp_var_60 = 0;
    php::Var tmp_var_61;
    php::Var tmp_var_62;
    php::Int tmp_var_63 = 0;
    php::Var tmp_var_64;
    php::Var tmp_var_65;
    php::Int tmp_var_66 = 0;
    php::Var tmp_var_67;
    php::Var tmp_var_68;
    php::Bool tmp_var_69 = 0;
    php::Var tmp_var_70;
    php::Var tmp_var_71;
    php::Int tmp_var_72 = 0;
    php::Var tmp_var_73;
    php::Var tmp_var_74;
    php::Var tmp_var_75;
    php::Var tmp_var_76;
    php::Var tmp_var_77;
    php::Var tmp_var_78;
    php::Bool tmp_var_79 = 0;
    php::Var tmp_var_80;
    php::Var tmp_var_81;
    php::Bool tmp_var_82 = 0;
    php::Var tmp_var_83;
    php::Var tmp_var_84;
    php::Float tmp_var_85 = 0;
    php::Var tmp_var_86;
    php::Var tmp_var_87;
    php::Float tmp_var_88 = 0;
    php::Var tmp_var_89;
    php::Var tmp_var_90;
    php::Bool tmp_var_91 = 0;
    php::Var tmp_var_92;
    php::Var tmp_var_93;
    php::Var tmp_var_94;
    php::Var tmp_var_95;
    php::Bool tmp_var_96 = 0;

    tmp_var_0 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    tmp_var_1 = format;
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(152))}}, tmp_var_3)) {
        tmp_var_2 = tmp_var_3;
    } else {
        tmp_var_2 = -1L;
    }
    tmp_var_4 = php::toInt(tmp_var_2);
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(153))}}, tmp_var_6)) {
        tmp_var_5 = tmp_var_6;
    } else {
        tmp_var_5 = false;
    }
    tmp_var_7 = php::toBool(tmp_var_5);
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(154))}}, tmp_var_9)) {
        tmp_var_8 = tmp_var_9;
    } else {
        tmp_var_8 = -1L;
    }
    tmp_var_10 = php::toInt(tmp_var_8);
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(155))}}, tmp_var_12)) {
        tmp_var_11 = tmp_var_12;
    } else {
        if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(156))}}, tmp_var_14)) {
        tmp_var_13 = tmp_var_14;
    } else {
        tmp_var_13 = false;
    }
        tmp_var_11 = tmp_var_13;
    }
    tmp_var_15 = php::toBool(tmp_var_11);
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(157))}}, tmp_var_17)) {
        tmp_var_16 = tmp_var_17;
    } else {
        tmp_var_16 = php::empty_string;
    }
    tmp_var_18 = php::toString(tmp_var_16);
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(158))}}, tmp_var_20)) {
        tmp_var_19 = tmp_var_20;
    } else {
        tmp_var_19 = false;
    }
    tmp_var_21 = php::toBool(tmp_var_19);
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(159))}}, tmp_var_23)) {
        tmp_var_22 = tmp_var_23;
    } else {
        tmp_var_22 = 6L;
    }
    tmp_var_24 = php::toInt(tmp_var_22);
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(160))}}, tmp_var_26)) {
        tmp_var_25 = tmp_var_26;
    } else {
        tmp_var_27 = php::toBool(php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(161))}}));
        tmp_var_25 = (php::toBool(tmp_var_27) || php::toBool(php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(162))}})));
    }
    tmp_var_28 = php::toBool(tmp_var_25);
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(161))}}, tmp_var_30)) {
        tmp_var_29 = tmp_var_30;
    } else {
        if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(162))}}, tmp_var_32)) {
        tmp_var_31 = tmp_var_32;
    } else {
        tmp_var_31 = 256L;
    }
        tmp_var_29 = tmp_var_31;
    }
    tmp_var_33 = php::toInt(tmp_var_29);
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(163))}}, tmp_var_35)) {
        tmp_var_34 = tmp_var_35;
    } else {
        tmp_var_34 = 1.0;
    }
    tmp_var_36 = php::toFloat(tmp_var_34);
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(164))}}, tmp_var_38)) {
        tmp_var_37 = tmp_var_38;
    } else {
        tmp_var_37 = false;
    }
    tmp_var_39 = php::toBool(tmp_var_37);
    tmp_var_42 = php::toInt((php::toBool(php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(165))}}))) ? ([&]() -> php::Int {
        tmp_var_40 = o.get(get_str(165));
        tmp_var_41 = php::same(tmp_var_40, php::true_);
        tmp_var_40.unset();
        if (php::toBool(tmp_var_41)) {
            return 60L;
        } else {
            return php::toInt(o.get(get_str(165)));
        }
    }()) : (-1L));
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(166))}}, tmp_var_44)) {
        tmp_var_43 = tmp_var_44;
    } else {
        tmp_var_43 = false;
    }
    tmp_var_45 = php::toBool(tmp_var_43);
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(167))}}, tmp_var_47)) {
        tmp_var_46 = tmp_var_47;
    } else {
        tmp_var_46 = 100L;
    }
    tmp_var_48 = php::toInt(tmp_var_46);
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(168))}}, tmp_var_50)) {
        tmp_var_49 = tmp_var_50;
    } else {
        tmp_var_49 = 8L;
    }
    tmp_var_51 = php::toInt(tmp_var_49);
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(169))}}, tmp_var_53)) {
        tmp_var_52 = tmp_var_53;
    } else {
        tmp_var_52 = php::empty_string;
    }
    tmp_var_54 = php::toString(tmp_var_52);
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(170))}}, tmp_var_56)) {
        tmp_var_55 = tmp_var_56;
    } else {
        tmp_var_55 = php::empty_string;
    }
    tmp_var_57 = php::toString(tmp_var_55);
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(142))}}, tmp_var_59)) {
        tmp_var_58 = tmp_var_59;
    } else {
        tmp_var_58 = false;
    }
    tmp_var_60 = php::toBool(tmp_var_58);
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(171))}}, tmp_var_62)) {
        tmp_var_61 = tmp_var_62;
    } else {
        tmp_var_61 = 256L;
    }
    tmp_var_63 = php::toInt(tmp_var_61);
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(172))}}, tmp_var_65)) {
        tmp_var_64 = tmp_var_65;
    } else {
        tmp_var_64 = 256L;
    }
    tmp_var_66 = php::toInt(tmp_var_64);
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(173))}}, tmp_var_68)) {
        tmp_var_67 = tmp_var_68;
    } else {
        tmp_var_67 = false;
    }
    tmp_var_69 = php::toBool(tmp_var_67);
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(174))}}, tmp_var_71)) {
        tmp_var_70 = tmp_var_71;
    } else {
        tmp_var_70 = -1L;
    }
    tmp_var_72 = php::toInt(tmp_var_70);
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(175))}}, tmp_var_74)) {
        tmp_var_73 = tmp_var_74;
    } else {
        tmp_var_73 = php::Array{};
    }
    tmp_var_75 = tmp_var_73;
    tmp_var_76 = php_pixelforge__image__csv(this_, tmp_var_75);
    tmp_var_75.unset();
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(176))}}, tmp_var_78)) {
        tmp_var_77 = tmp_var_78;
    } else {
        tmp_var_77 = false;
    }
    tmp_var_79 = php::toBool(tmp_var_77);
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(177))}}, tmp_var_81)) {
        tmp_var_80 = tmp_var_81;
    } else {
        tmp_var_80 = false;
    }
    tmp_var_82 = php::toBool(tmp_var_80);
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(178))}}, tmp_var_84)) {
        tmp_var_83 = tmp_var_84;
    } else {
        tmp_var_83 = 0L;
    }
    tmp_var_85 = php::toFloat(tmp_var_83);
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(179))}}, tmp_var_87)) {
        tmp_var_86 = tmp_var_87;
    } else {
        tmp_var_86 = 3L;
    }
    tmp_var_88 = php::toFloat(tmp_var_86);
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(180))}}, tmp_var_90)) {
        tmp_var_89 = tmp_var_90;
    } else {
        tmp_var_89 = false;
    }
    tmp_var_91 = php::toBool(tmp_var_89);
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(181))}}, tmp_var_93)) {
        tmp_var_92 = tmp_var_93;
    } else {
        if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(182))}}, tmp_var_95)) {
        tmp_var_94 = tmp_var_95;
    } else {
        tmp_var_94 = true;
    }
        tmp_var_92 = tmp_var_94;
    }
    tmp_var_96 = php::toBool(tmp_var_92);
    php_pixelforge_output(php::deindirect(tmp_var_0), tmp_var_1, php::toInt(tmp_var_4), php::toBool(tmp_var_7), php::toInt(tmp_var_10), php::toBool(tmp_var_15), tmp_var_18, php::toBool(tmp_var_21), php::toInt(tmp_var_24), php::toBool(tmp_var_28), php::toInt(tmp_var_33), php::toFloat(tmp_var_36), php::toBool(tmp_var_39), php::toInt(tmp_var_42), php::toBool(tmp_var_45), php::toInt(tmp_var_48), php::toInt(tmp_var_51), tmp_var_54, tmp_var_57, php::toBool(tmp_var_60), php::toInt(tmp_var_63), php::toInt(tmp_var_66), php::toBool(tmp_var_69), php::toInt(tmp_var_72), tmp_var_76, php::toBool(tmp_var_79), php::toBool(tmp_var_82), php::toFloat(tmp_var_85), php::toFloat(tmp_var_88), php::toBool(tmp_var_91), php::toBool(tmp_var_96));
    tmp_var_0.unset();
    tmp_var_1.unset();
    tmp_var_18.unset();
    tmp_var_54.unset();
    tmp_var_57.unset();
    tmp_var_76.unset();
    return this_;
}

php::Object php_pixelforge__image__tile(php::Object &this_, php::Array o) {
    php::Array bg;
    php::Var tmp_var_0;
    php::Var tmp_var_1;
    php::Var tmp_var_2;
    php::Object tmp_var_3;
    php::Var tmp_var_4;
    php::Var tmp_var_5;
    php::Var tmp_var_6;
    php::Int tmp_var_7 = 0;
    php::Var tmp_var_8;
    php::Var tmp_var_9;
    php::Int tmp_var_10 = 0;
    php::Var tmp_var_11;
    php::Var tmp_var_12;
    php::Int tmp_var_13 = 0;
    php::Var tmp_var_14;
    php::Var tmp_var_15;
    php::Var tmp_var_16;
    php::Var tmp_var_17;
    php::Var tmp_var_18;
    php::Var tmp_var_19;
    php::Var tmp_var_20;
    php::Var tmp_var_21;
    php::Var tmp_var_22;
    php::Var tmp_var_23;
    php::Var tmp_var_24;
    php::Bool tmp_var_25 = 0;
    php::Var tmp_var_26;
    php::Var tmp_var_27;
    php::Var tmp_var_28;
    php::Var tmp_var_29;
    php::Bool tmp_var_30 = 0;
    php::Var tmp_var_31;
    php::Var tmp_var_32;
    php::Var tmp_var_33;
    php::Var tmp_var_34;
    php::Var tmp_var_35;
    php::Var tmp_var_36;
    php::Var tmp_var_37;
    php::Var tmp_var_38;
    php::Var tmp_var_39;
    php::Var tmp_var_40;
    Z_PTR_P(tmp_var_3.ptr()) = get_persistent_class(PersistentClassId{1}, get_str(26));

    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(16))}}, tmp_var_1)) {
        tmp_var_0 = tmp_var_1;
    } else {
        tmp_var_0 = get_str(183);
    }
    tmp_var_2 = tmp_var_0;
    bg = php_pixelforge__color__parse(tmp_var_3, tmp_var_2);
    tmp_var_2.unset();
    tmp_var_4 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(184))}}, tmp_var_6)) {
        tmp_var_5 = tmp_var_6;
    } else {
        tmp_var_5 = 256L;
    }
    tmp_var_7 = php::toInt(tmp_var_5);
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(185))}}, tmp_var_9)) {
        tmp_var_8 = tmp_var_9;
    } else {
        tmp_var_8 = 0L;
    }
    tmp_var_10 = php::toInt(tmp_var_8);
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(87))}}, tmp_var_12)) {
        tmp_var_11 = tmp_var_12;
    } else {
        tmp_var_11 = 0L;
    }
    tmp_var_13 = php::toInt(tmp_var_11);
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(186))}}, tmp_var_15)) {
        tmp_var_14 = tmp_var_15;
    } else {
        tmp_var_14 = get_str(187);
    }
    tmp_var_16 = php::toString(tmp_var_14);
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(188))}}, tmp_var_18)) {
        tmp_var_17 = tmp_var_18;
    } else {
        tmp_var_17 = get_str(189);
    }
    tmp_var_19 = php::toString(tmp_var_17);
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(13))}}, tmp_var_21)) {
        tmp_var_20 = tmp_var_21;
    } else {
        tmp_var_20 = php::empty_string;
    }
    tmp_var_22 = php::toString(tmp_var_20);
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(190))}}, tmp_var_24)) {
        tmp_var_23 = tmp_var_24;
    } else {
        tmp_var_23 = false;
    }
    tmp_var_25 = php::toBool(tmp_var_23);
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(62))}}, tmp_var_27)) {
        tmp_var_26 = tmp_var_27;
    } else {
        if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(191))}}, tmp_var_29)) {
        tmp_var_28 = tmp_var_29;
    } else {
        tmp_var_28 = false;
    }
        tmp_var_26 = tmp_var_28;
    }
    tmp_var_30 = php::toBool(tmp_var_26);
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(192))}}, tmp_var_32)) {
        tmp_var_31 = tmp_var_32;
    } else {
        tmp_var_31 = php::empty_string;
    }
    tmp_var_33 = php::toString(tmp_var_31);
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(193))}}, tmp_var_35)) {
        tmp_var_34 = tmp_var_35;
    } else {
        tmp_var_34 = php::empty_string;
    }
    tmp_var_36 = php::toString(tmp_var_34);
    tmp_var_37 = bg.get(0L);
    tmp_var_38 = bg.get(1L);
    tmp_var_39 = bg.get(2L);
    tmp_var_40 = bg.get(3L);
    php_pixelforge_tile(php::deindirect(tmp_var_4), php::toInt(tmp_var_7), php::toInt(tmp_var_10), php::toInt(tmp_var_13), tmp_var_16, tmp_var_19, tmp_var_22, php::toBool(tmp_var_25), php::toBool(tmp_var_30), tmp_var_33, tmp_var_36, php::toFloatArgExact(php::deindirect(tmp_var_37), get_str(194), 12, get_str(19)), php::toFloatArgExact(php::deindirect(tmp_var_38), get_str(194), 13, get_str(20)), php::toFloatArgExact(php::deindirect(tmp_var_39), get_str(194), 14, get_str(21)), php::toFloatArgExact(php::deindirect(tmp_var_40), get_str(194), 15, get_str(22)));
    tmp_var_4.unset();
    tmp_var_16.unset();
    tmp_var_19.unset();
    tmp_var_22.unset();
    tmp_var_33.unset();
    tmp_var_36.unset();
    tmp_var_37.unset();
    tmp_var_38.unset();
    tmp_var_39.unset();
    tmp_var_40.unset();
    return this_;
}

php::Object php_pixelforge__image__timeout(php::Object &this_, php::Array o) {
    php::Var tmp_var_0;
    php::Var tmp_var_1;
    php::Var tmp_var_2;
    php::Float tmp_var_3 = 0;

    tmp_var_0 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    if (php::exists(o, {{php::ArrayDimFetch, php::Var(get_str(195))}}, tmp_var_2)) {
        tmp_var_1 = tmp_var_2;
    } else {
        tmp_var_1 = 0L;
    }
    tmp_var_3 = php::toFloat(tmp_var_1);
    php_pixelforge_timeout(php::deindirect(tmp_var_0), php::toFloat(tmp_var_3));
    tmp_var_0.unset();
    return this_;
}

php::Object php_pixelforge__image__keepmetadata(php::Object &this_) {
    php::Int tmp_var_0 = 0;
    php::Object tmp_var_1;

    tmp_var_0 = php::toInt(31L);
    tmp_var_1 = (php_pixelforge__image__keep(this_, php::toInt(tmp_var_0)));
    return tmp_var_1;
}

php::Object php_pixelforge__image__withmetadata(php::Object &this_) {
    php::Object tmp_var_0;

    tmp_var_0 = (php_pixelforge__image__keepmetadata(this_));
    return tmp_var_0;
}

php::Object php_pixelforge__image__keepexif(php::Object &this_) {
    php::Int tmp_var_0 = 0;
    php::Int tmp_var_1 = 0;
    php::Int tmp_var_2 = 0;
    php::Object tmp_var_3;
    php::Int &_object_prop_this___keepFlags = this_.attrInt(get_persistent_prop(PersistentPropertyId{1}, get_str(59), get_str(1)));

    tmp_var_0 = php::toInt(_object_prop_this___keepFlags);
    tmp_var_1 = php::toInt(1L);
    tmp_var_2 = php::toInt(((tmp_var_0) | (tmp_var_1)));
    tmp_var_3 = (php_pixelforge__image__keep(this_, php::toInt(tmp_var_2)));
    return tmp_var_3;
}

php::Object php_pixelforge__image__keepiccprofile(php::Object &this_) {
    php::Int tmp_var_0 = 0;
    php::Int tmp_var_1 = 0;
    php::Int tmp_var_2 = 0;
    php::Object tmp_var_3;
    php::Int &_object_prop_this___keepFlags = this_.attrInt(get_persistent_prop(PersistentPropertyId{1}, get_str(59), get_str(1)));

    tmp_var_0 = php::toInt(_object_prop_this___keepFlags);
    tmp_var_1 = php::toInt(8L);
    tmp_var_2 = php::toInt(((tmp_var_0) | (tmp_var_1)));
    tmp_var_3 = (php_pixelforge__image__keep(this_, php::toInt(tmp_var_2)));
    return tmp_var_3;
}

php::Object php_pixelforge__image__withiccprofile(php::Object &this_, php::Str profile) {
    php::Var tmp_var_0;

    tmp_var_0 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    php_pixelforge_icc(php::deindirect(tmp_var_0), profile);
    tmp_var_0.unset();
    return this_;
}

php::Object php_pixelforge__image__withexif(php::Object &this_, php::Array exif) {
    php::Var tmp_var_0;
    php::Var tmp_var_1;

    tmp_var_0 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    tmp_var_1 = php_pixelforge__image__flattenexif(this_, exif);
    php_pixelforge_exif(php::deindirect(tmp_var_0), tmp_var_1, php::toBool(false));
    tmp_var_0.unset();
    tmp_var_1.unset();
    return this_;
}

php::Object php_pixelforge__image__withexifmerge(php::Object &this_, php::Array exif) {
    php::Var tmp_var_0;
    php::Var tmp_var_1;

    tmp_var_0 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    tmp_var_1 = php_pixelforge__image__flattenexif(this_, exif);
    php_pixelforge_exif(php::deindirect(tmp_var_0), tmp_var_1, php::toBool(true));
    tmp_var_0.unset();
    tmp_var_1.unset();
    return this_;
}

php::Str php_pixelforge__image__flattenexif(php::Object &this_, php::Array exif) {
    php::Array out;
    php::Var tags;
    php::Var ifd;
    php::Var tmp_var_2;
    php::Var tag;
    php::Var value;
    zend_function * tmp_var_4;
    php::Var tmp_var_5;
    zend_class_entry *tmp_var_1 = get_persistent_class(PersistentClassId{0}, get_str(1));

    out = php::Array{};
    {
        php::ForeachIterator tmp_var_0{exif, false, tmp_var_1};
        while (tmp_var_0.nextKeyValue(ifd, tags)) {

            tmp_var_2 = tags;
            {
                php::ForeachIterator tmp_var_3{tmp_var_2, false, tmp_var_1};
                while (tmp_var_3.next()) {
                    tag = tmp_var_3.key();
                    value = tmp_var_3.value();
                    out.appendValue(php::concat({php::toString(ifd), get_str(198), php::toString(tag), get_str(198), php::toString(value)}));
                }
            }
        }
    }
    if (get_function_resolution_cache(FunctionResolutionCacheId{8}) == 0) { get_function_resolution_cache(FunctionResolutionCacheId{8}) = php::fn::function_exists(get_str(199)) ? 1 : 2; }
    tmp_var_4 = get_function_resolution_cache(FunctionResolutionCacheId{8}) == 1 ? get_func(RequestFuncId{6}, get_str(199)) : get_persistent_func(PersistentFuncId{6}, get_str(200));
    tmp_var_5 = (php::call(tmp_var_4, php::VarList{get_str(201), out}));
    if (UNEXPECTED(!(tmp_var_5.isString()))) {
        php::throwReturnTypeError(tmp_var_5, get_str(202), get_str(203), true);
    }
    return tmp_var_5;
}

php::Object php_pixelforge__image__keepxmp(php::Object &this_) {
    php::Int tmp_var_0 = 0;
    php::Int tmp_var_1 = 0;
    php::Int tmp_var_2 = 0;
    php::Object tmp_var_3;
    php::Int &_object_prop_this___keepFlags = this_.attrInt(get_persistent_prop(PersistentPropertyId{1}, get_str(59), get_str(1)));

    tmp_var_0 = php::toInt(_object_prop_this___keepFlags);
    tmp_var_1 = php::toInt(2L);
    tmp_var_2 = php::toInt(((tmp_var_0) | (tmp_var_1)));
    tmp_var_3 = (php_pixelforge__image__keep(this_, php::toInt(tmp_var_2)));
    return tmp_var_3;
}

php::Object php_pixelforge__image__keep(php::Object &this_, php::Int flags) {
    php::Var tmp_var_0;
    php::Int &_object_prop_this___keepFlags = this_.attrInt(get_persistent_prop(PersistentPropertyId{1}, get_str(59), get_str(1)));

    _object_prop_this___keepFlags = flags;
    tmp_var_0 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    php_pixelforge_keep(php::deindirect(tmp_var_0), php::toInt(flags));
    tmp_var_0.unset();
    return this_;
}

php::Array php_pixelforge__image__tofile(php::Object &this_, php::Str path) {
    php::Var tmp_var_0;
    php::Array tmp_var_1;

    tmp_var_0 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    tmp_var_1 = (php_pixelforge_to_file(php::deindirect(tmp_var_0), path));
    tmp_var_0.unset();
    return tmp_var_1;
}

php::Str php_pixelforge__image__tobuffer(php::Object &this_, php::Var format) {
    php::Array r;
    php::Var tmp_var_0;
    php::Str tmp_var_1;
    php::Var tmp_var_2;
    if (UNEXPECTED(!(format.isNull() || format.isString()))) {
        php::throwArgumentTypeError(format, get_str(205), 1, get_str(206), get_str(207));
    }

    tmp_var_0 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    if (php::exists(format)) {
        tmp_var_1 = php::toString(format);
    } else {
        tmp_var_1 = php::toString(php::empty_string);
    }
    r = php_pixelforge_to_buffer(php::deindirect(tmp_var_0), tmp_var_1);
    tmp_var_0.unset();
    tmp_var_2 = (r.get(get_str(204)));
    if (UNEXPECTED(!(tmp_var_2.isString()))) {
        php::throwReturnTypeError(tmp_var_2, get_str(205), get_str(203), true);
    }
    return tmp_var_2;
}

php::Array php_pixelforge__image__tobufferwithinfo(php::Object &this_, php::Var format) {
    php::Var tmp_var_0;
    php::Str tmp_var_1;
    php::Array tmp_var_2;
    if (UNEXPECTED(!(format.isNull() || format.isString()))) {
        php::throwArgumentTypeError(format, get_str(208), 1, get_str(206), get_str(207));
    }

    tmp_var_0 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    if (php::exists(format)) {
        tmp_var_1 = php::toString(format);
    } else {
        tmp_var_1 = php::toString(php::empty_string);
    }
    tmp_var_2 = (php_pixelforge_to_buffer(php::deindirect(tmp_var_0), tmp_var_1));
    tmp_var_0.unset();
    return tmp_var_2;
}

php::Array php_pixelforge__image__metadata(php::Object &this_) {
    php::Var tmp_var_0;
    php::Array tmp_var_1;

    tmp_var_0 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    tmp_var_1 = (php_pixelforge_metadata(php::deindirect(tmp_var_0)));
    tmp_var_0.unset();
    return tmp_var_1;
}

php::Array php_pixelforge__image__stats(php::Object &this_) {
    php::Var tmp_var_0;
    php::Array tmp_var_1;

    tmp_var_0 = this_.attr(get_persistent_prop(PersistentPropertyId{0}, get_str(0), get_str(1)), php::AttrMode::Get);
    tmp_var_1 = (php_pixelforge_stats(php::deindirect(tmp_var_0)));
    tmp_var_0.unset();
    return tmp_var_1;
}

php::Str php_pixelforge__image__csv(php::Object &this_, php::Var v) {
    zend_function * tmp_var_0;
    php::Array parts;
    php::Var tmp_var_1;
    php::Var x;
    zend_function * tmp_var_4;
    php::Var tmp_var_5;
    php::Str tmp_var_6;
    zend_class_entry *tmp_var_3 = get_persistent_class(PersistentClassId{0}, get_str(1));

    if (get_function_resolution_cache(FunctionResolutionCacheId{9}) == 0) { get_function_resolution_cache(FunctionResolutionCacheId{9}) = php::fn::function_exists(get_str(46)) ? 1 : 2; }
    tmp_var_0 = get_function_resolution_cache(FunctionResolutionCacheId{9}) == 1 ? get_func(RequestFuncId{0}, get_str(46)) : get_persistent_func(PersistentFuncId{0}, get_str(47));
    if (php::toBool(php::call(tmp_var_0, php::VarList{v}))) {
        parts = php::Array{};

        tmp_var_1 = v;
        {
            php::ForeachIterator tmp_var_2{tmp_var_1, false, tmp_var_3};
            while (tmp_var_2.next()) {
                x = tmp_var_2.value();
                parts.appendValue(php::toString(php::toFloat(x)));
            }
        }
        if (get_function_resolution_cache(FunctionResolutionCacheId{10}) == 0) { get_function_resolution_cache(FunctionResolutionCacheId{10}) = php::fn::function_exists(get_str(199)) ? 1 : 2; }
        tmp_var_4 = get_function_resolution_cache(FunctionResolutionCacheId{10}) == 1 ? get_func(RequestFuncId{6}, get_str(199)) : get_persistent_func(PersistentFuncId{6}, get_str(200));
        tmp_var_5 = (php::call(tmp_var_4, php::VarList{get_str(209), parts}));
        if (UNEXPECTED(!(tmp_var_5.isString()))) {
            php::throwReturnTypeError(tmp_var_5, get_str(210), get_str(203), true);
        }
        return tmp_var_5;
    }
    tmp_var_6 = (php::toString(php::toFloat(v)));
    return tmp_var_6;
}


php::Str php_pixelforge__gravity__normalise(php::Object &this_, php::Str g) {
    zend_function * tmp_var_0;
    zend_function * tmp_var_1;
    php::Var tmp_var_2;
    php::Array map;
    php::Var tmp_var_3;
    php::Var tmp_var_4;
    php::Var tmp_var_5;

    if (get_function_resolution_cache(FunctionResolutionCacheId{11}) == 0) { get_function_resolution_cache(FunctionResolutionCacheId{11}) = php::fn::function_exists(get_str(211)) ? 1 : 2; }
    tmp_var_0 = get_function_resolution_cache(FunctionResolutionCacheId{11}) == 1 ? get_func(RequestFuncId{7}, get_str(211)) : get_persistent_func(PersistentFuncId{7}, get_str(212));
    if (get_function_resolution_cache(FunctionResolutionCacheId{12}) == 0) { get_function_resolution_cache(FunctionResolutionCacheId{12}) = php::fn::function_exists(get_str(213)) ? 1 : 2; }
    tmp_var_1 = get_function_resolution_cache(FunctionResolutionCacheId{12}) == 1 ? get_persistent_func(PersistentFuncId{8}, get_str(213)) : get_persistent_func(PersistentFuncId{9}, get_str(214));
    tmp_var_2 = php::call(tmp_var_1, php::VarList{g});
    g = php::call(tmp_var_0, php::VarList{tmp_var_2});
    tmp_var_2.unset();
    map = php::Array{
        { get_str(191).str(), php::Var(get_str(62)) }, 
        { get_str(62).str(), php::Var(get_str(62)) }, 
        { get_str(44).str(), php::Var(get_str(215)) }, 
        { get_str(217).str(), php::Var(get_str(216)) }, 
        { get_str(218).str(), php::Var(get_str(216)) }, 
        { get_str(77).str(), php::Var(get_str(219)) }, 
        { get_str(221).str(), php::Var(get_str(220)) }, 
        { get_str(222).str(), php::Var(get_str(220)) }, 
        { get_str(76).str(), php::Var(get_str(223)) }, 
        { get_str(225).str(), php::Var(get_str(224)) }, 
        { get_str(226).str(), php::Var(get_str(224)) }, 
        { get_str(31).str(), php::Var(get_str(227)) }, 
        { get_str(229).str(), php::Var(get_str(228)) }, 
        { get_str(230).str(), php::Var(get_str(228)) }
    };
    if (php::exists(map, {{php::ArrayDimFetch, php::Var(g)}}, tmp_var_4)) {
        tmp_var_3 = tmp_var_4;
    } else {
        tmp_var_3 = g;
    }
    tmp_var_5 = (tmp_var_3);
    if (UNEXPECTED(!(tmp_var_5.isString()))) {
        php::throwReturnTypeError(tmp_var_5, get_str(231), get_str(203), true);
    }
    return tmp_var_5;
}


php::Array php_pixelforge__color__parse(php::Object &this_, php::Var c) {
    zend_function * tmp_var_0;
    php::Float r = 0;
    php::Var tmp_var_1;
    php::Var tmp_var_2;
    php::Var tmp_var_3;
    php::Var tmp_var_4;
    php::Float g = 0;
    php::Var tmp_var_5;
    php::Var tmp_var_6;
    php::Var tmp_var_7;
    php::Var tmp_var_8;
    php::Float b = 0;
    php::Var tmp_var_9;
    php::Var tmp_var_10;
    php::Var tmp_var_11;
    php::Var tmp_var_12;
    php::Float a = 0;
    php::Var tmp_var_13;
    php::Var tmp_var_14;
    php::Var tmp_var_15;
    php::Var tmp_var_16;
    php::Array tmp_var_17;
    php::Var s;
    zend_function * tmp_var_18;
    zend_function * tmp_var_19;
    php::Var tmp_var_20;
    php::Array tmp_var_21;
    php::Array tmp_var_22;
    php::Array tmp_var_23;
    zend_function * tmp_var_24;
    zend_function * tmp_var_25;
    zend_function * tmp_var_26;
    php::Var tmp_var_27;
    php::Bool tmp_var_28 = 0;
    zend_function * tmp_var_29;
    php::Var tmp_var_30;
    php::Bool tmp_var_31 = 0;
    php::Str e;
    php::Int i = 0;
    zend_function * tmp_var_32;
    php::Var tmp_var_33;
    php::Var tmp_var_35;
    php::Var tmp_var_36;
    php::Var tmp_var_37;
    zend_function * tmp_var_38;
    php::Var tmp_var_39;
    php::Bool tmp_var_40 = 0;
    zend_function * tmp_var_41;
    php::Var tmp_var_42;
    php::Bool tmp_var_43 = 0;
    zend_function * tmp_var_45;
    php::Var tmp_var_46;
    zend_function * tmp_var_47;
    zend_function * tmp_var_48;
    php::Var tmp_var_49;
    php::Var tmp_var_50;
    php::Float tmp_var_51 = 0;
    zend_function * tmp_var_52;
    zend_function * tmp_var_53;
    php::Var tmp_var_54;
    php::Float tmp_var_55 = 0;
    zend_function * tmp_var_56;
    zend_function * tmp_var_57;
    php::Var tmp_var_58;
    php::Float tmp_var_59 = 0;
    zend_function * tmp_var_60;
    zend_function * tmp_var_61;
    php::Var tmp_var_62;
    php::Float tmp_var_63 = 0;
    php::Array tmp_var_64;
    zend_class_entry *tmp_var_44 = get_persistent_class(PersistentClassId{3}, get_str(135));

    if (get_function_resolution_cache(FunctionResolutionCacheId{13}) == 0) { get_function_resolution_cache(FunctionResolutionCacheId{13}) = php::fn::function_exists(get_str(46)) ? 1 : 2; }
    tmp_var_0 = get_function_resolution_cache(FunctionResolutionCacheId{13}) == 1 ? get_func(RequestFuncId{0}, get_str(46)) : get_persistent_func(PersistentFuncId{0}, get_str(47));
    if (php::toBool(php::call(tmp_var_0, php::VarList{c}))) {
        if (php::exists(c, {{php::ArrayDimFetch, php::Var(get_str(19))}}, tmp_var_2)) {
            tmp_var_1 = tmp_var_2;
        } else {
            if (php::exists(c, {{php::ArrayDimFetch, php::Var(0L)}}, tmp_var_4)) {
            tmp_var_3 = tmp_var_4;
        } else {
            tmp_var_3 = 0L;
        }
            tmp_var_1 = tmp_var_3;
        }
        r = php::toFloat(tmp_var_1);
        if (php::exists(c, {{php::ArrayDimFetch, php::Var(get_str(20))}}, tmp_var_6)) {
            tmp_var_5 = tmp_var_6;
        } else {
            if (php::exists(c, {{php::ArrayDimFetch, php::Var(1L)}}, tmp_var_8)) {
            tmp_var_7 = tmp_var_8;
        } else {
            tmp_var_7 = 0L;
        }
            tmp_var_5 = tmp_var_7;
        }
        g = php::toFloat(tmp_var_5);
        if (php::exists(c, {{php::ArrayDimFetch, php::Var(get_str(21))}}, tmp_var_10)) {
            tmp_var_9 = tmp_var_10;
        } else {
            if (php::exists(c, {{php::ArrayDimFetch, php::Var(2L)}}, tmp_var_12)) {
            tmp_var_11 = tmp_var_12;
        } else {
            tmp_var_11 = 0L;
        }
            tmp_var_9 = tmp_var_11;
        }
        b = php::toFloat(tmp_var_9);
        if (php::exists(c, {{php::ArrayDimFetch, php::Var(get_str(112))}}, tmp_var_14)) {
            tmp_var_13 = tmp_var_14;
        } else {
            if (php::exists(c, {{php::ArrayDimFetch, php::Var(3L)}}, tmp_var_16)) {
            tmp_var_15 = tmp_var_16;
        } else {
            tmp_var_15 = 1L;
        }
            tmp_var_13 = tmp_var_15;
        }
        a = php::toFloat(tmp_var_13);
        tmp_var_17 = (php::Array{
            php::Var(r), 
            php::Var(g), 
            php::Var(b), 
            php::Var(((a) * (255.0)))
        });
        return tmp_var_17;
    }
    if (get_function_resolution_cache(FunctionResolutionCacheId{14}) == 0) { get_function_resolution_cache(FunctionResolutionCacheId{14}) = php::fn::function_exists(get_str(211)) ? 1 : 2; }
    tmp_var_18 = get_function_resolution_cache(FunctionResolutionCacheId{14}) == 1 ? get_func(RequestFuncId{7}, get_str(211)) : get_persistent_func(PersistentFuncId{7}, get_str(212));
    if (get_function_resolution_cache(FunctionResolutionCacheId{15}) == 0) { get_function_resolution_cache(FunctionResolutionCacheId{15}) = php::fn::function_exists(get_str(213)) ? 1 : 2; }
    tmp_var_19 = get_function_resolution_cache(FunctionResolutionCacheId{15}) == 1 ? get_persistent_func(PersistentFuncId{8}, get_str(213)) : get_persistent_func(PersistentFuncId{9}, get_str(214));
    tmp_var_20 = php::call(tmp_var_19, php::VarList{php::toString(c)});
    s = php::call(tmp_var_18, php::VarList{tmp_var_20});
    tmp_var_20.unset();
    if (php::toBool(php::same(s, get_str(232)))) {
        tmp_var_21 = (php::Array{
            php::Var(0.0), 
            php::Var(0.0), 
            php::Var(0.0), 
            php::Var(0.0)
        });
        return tmp_var_21;
    }
    if (php::toBool(php::same(s, get_str(233)))) {
        tmp_var_22 = (php::Array{
            php::Var(255.0), 
            php::Var(255.0), 
            php::Var(255.0), 
            php::Var(255.0)
        });
        return tmp_var_22;
    }
    if (php::toBool(php::same(s, get_str(234)))) {
        tmp_var_23 = (php::Array{
            php::Var(0.0), 
            php::Var(0.0), 
            php::Var(0.0), 
            php::Var(255.0)
        });
        return tmp_var_23;
    }
    if (get_function_resolution_cache(FunctionResolutionCacheId{16}) == 0) { get_function_resolution_cache(FunctionResolutionCacheId{16}) = php::fn::function_exists(get_str(235)) ? 1 : 2; }
    tmp_var_24 = get_function_resolution_cache(FunctionResolutionCacheId{16}) == 1 ? get_func(RequestFuncId{8}, get_str(235)) : get_persistent_func(PersistentFuncId{10}, get_str(236));
    if (php::toBool(php::call(tmp_var_24, php::VarList{s, get_str(237)}))) {
        if (get_function_resolution_cache(FunctionResolutionCacheId{17}) == 0) { get_function_resolution_cache(FunctionResolutionCacheId{17}) = php::fn::function_exists(get_str(238)) ? 1 : 2; }
        tmp_var_25 = get_function_resolution_cache(FunctionResolutionCacheId{17}) == 1 ? get_func(RequestFuncId{9}, get_str(238)) : get_persistent_func(PersistentFuncId{11}, get_str(239));
        s = php::call(tmp_var_25, php::VarList{s, 1L});
    }
    if (get_function_resolution_cache(FunctionResolutionCacheId{18}) == 0) { get_function_resolution_cache(FunctionResolutionCacheId{18}) = php::fn::function_exists(get_str(50)) ? 1 : 2; }
    tmp_var_26 = get_function_resolution_cache(FunctionResolutionCacheId{18}) == 1 ? get_func(RequestFuncId{1}, get_str(50)) : get_persistent_func(PersistentFuncId{1}, get_str(51));
    tmp_var_27 = php::call(tmp_var_26, php::VarList{s});
    tmp_var_28 = php::toBool(php::same(tmp_var_27, 3L));
    tmp_var_27.unset();
    if (php::toBool([&]() -> bool {
        if (!(php::toBool(tmp_var_28))) {
            if (get_function_resolution_cache(FunctionResolutionCacheId{19}) == 0) { get_function_resolution_cache(FunctionResolutionCacheId{19}) = php::fn::function_exists(get_str(50)) ? 1 : 2; }
            tmp_var_29 = get_function_resolution_cache(FunctionResolutionCacheId{19}) == 1 ? get_func(RequestFuncId{1}, get_str(50)) : get_persistent_func(PersistentFuncId{1}, get_str(51));
            tmp_var_30 = php::call(tmp_var_29, php::VarList{s});
            tmp_var_31 = php::toBool(php::same(tmp_var_30, 4L));
            tmp_var_30.unset();
            return php::toBool(tmp_var_31);
        }
        return true;
    }())) {
        e = php::empty_string;
        i = php::toInt(0L);
        
        for (;[&]() -> bool {        bool tmp_var_34 = true;
        if (get_function_resolution_cache(FunctionResolutionCacheId{20}) == 0) { get_function_resolution_cache(FunctionResolutionCacheId{20}) = php::fn::function_exists(get_str(50)) ? 1 : 2; }
        tmp_var_32 = get_function_resolution_cache(FunctionResolutionCacheId{20}) == 1 ? get_func(RequestFuncId{1}, get_str(50)) : get_persistent_func(PersistentFuncId{1}, get_str(51));
        tmp_var_33 = php::call(tmp_var_32, php::VarList{s});
        tmp_var_35 = php::toBool(((php::Var(i)) < (php::Var(tmp_var_33))));
        tmp_var_33.unset();
        tmp_var_34 = php::toBool(tmp_var_35);
        return tmp_var_34;        }(); ++i) {
            tmp_var_36 = s.item(i, false);
            tmp_var_37 = s.item(i, false);
            (e.append(php::concat({php::toString(tmp_var_36), php::toString(tmp_var_37)})), e);
            tmp_var_36.unset();
            tmp_var_37.unset();
        }
        s = e;
    }
    if (get_function_resolution_cache(FunctionResolutionCacheId{21}) == 0) { get_function_resolution_cache(FunctionResolutionCacheId{21}) = php::fn::function_exists(get_str(50)) ? 1 : 2; }
    tmp_var_38 = get_function_resolution_cache(FunctionResolutionCacheId{21}) == 1 ? get_func(RequestFuncId{1}, get_str(50)) : get_persistent_func(PersistentFuncId{1}, get_str(51));
    tmp_var_39 = php::call(tmp_var_38, php::VarList{s});
    tmp_var_40 = php::toBool(!(php::same(tmp_var_39, 6L)));
    tmp_var_39.unset();
    if (php::toBool([&]() -> bool {
        if (php::toBool(tmp_var_40)) {
            if (get_function_resolution_cache(FunctionResolutionCacheId{22}) == 0) { get_function_resolution_cache(FunctionResolutionCacheId{22}) = php::fn::function_exists(get_str(50)) ? 1 : 2; }
            tmp_var_41 = get_function_resolution_cache(FunctionResolutionCacheId{22}) == 1 ? get_func(RequestFuncId{1}, get_str(50)) : get_persistent_func(PersistentFuncId{1}, get_str(51));
            tmp_var_42 = php::call(tmp_var_41, php::VarList{s});
            tmp_var_43 = php::toBool(!(php::same(tmp_var_42, 8L)));
            tmp_var_42.unset();
            return php::toBool(tmp_var_43);
        }
        return false;
    }())) {
        php::throwException(php::newObject(tmp_var_44, php::VarList{php::concat({get_str(240), php::toString(c)})}));
    }
    a = php::toFloat([&]() -> php::Float {
        if (get_function_resolution_cache(FunctionResolutionCacheId{23}) == 0) { get_function_resolution_cache(FunctionResolutionCacheId{23}) = php::fn::function_exists(get_str(50)) ? 1 : 2; }
        tmp_var_45 = get_function_resolution_cache(FunctionResolutionCacheId{23}) == 1 ? get_func(RequestFuncId{1}, get_str(50)) : get_persistent_func(PersistentFuncId{1}, get_str(51));
        tmp_var_46 = php::call(tmp_var_45, php::VarList{s});
        tmp_var_50 = php::same(tmp_var_46, 8L);
        tmp_var_46.unset();
        if (php::toBool(tmp_var_50)) {
            if (get_function_resolution_cache(FunctionResolutionCacheId{24}) == 0) { get_function_resolution_cache(FunctionResolutionCacheId{24}) = php::fn::function_exists(get_str(241)) ? 1 : 2; }
            tmp_var_47 = get_function_resolution_cache(FunctionResolutionCacheId{24}) == 1 ? get_func(RequestFuncId{10}, get_str(241)) : get_persistent_func(PersistentFuncId{12}, get_str(242));
            if (get_function_resolution_cache(FunctionResolutionCacheId{25}) == 0) { get_function_resolution_cache(FunctionResolutionCacheId{25}) = php::fn::function_exists(get_str(238)) ? 1 : 2; }
            tmp_var_48 = get_function_resolution_cache(FunctionResolutionCacheId{25}) == 1 ? get_func(RequestFuncId{9}, get_str(238)) : get_persistent_func(PersistentFuncId{11}, get_str(239));
            tmp_var_49 = php::call(tmp_var_48, php::VarList{s, 6L, 2L});
            tmp_var_51 = php::toFloat(php::call(tmp_var_47, php::VarList{tmp_var_49}));
            tmp_var_49.unset();
            return tmp_var_51;
        } else {
            return 255.0;
        }
    }());
    if (get_function_resolution_cache(FunctionResolutionCacheId{26}) == 0) { get_function_resolution_cache(FunctionResolutionCacheId{26}) = php::fn::function_exists(get_str(241)) ? 1 : 2; }
    tmp_var_52 = get_function_resolution_cache(FunctionResolutionCacheId{26}) == 1 ? get_func(RequestFuncId{10}, get_str(241)) : get_persistent_func(PersistentFuncId{12}, get_str(242));
    if (get_function_resolution_cache(FunctionResolutionCacheId{27}) == 0) { get_function_resolution_cache(FunctionResolutionCacheId{27}) = php::fn::function_exists(get_str(238)) ? 1 : 2; }
    tmp_var_53 = get_function_resolution_cache(FunctionResolutionCacheId{27}) == 1 ? get_func(RequestFuncId{9}, get_str(238)) : get_persistent_func(PersistentFuncId{11}, get_str(239));
    tmp_var_54 = php::call(tmp_var_53, php::VarList{s, 0L, 2L});
    tmp_var_55 = php::toFloat(php::call(tmp_var_52, php::VarList{tmp_var_54}));
    tmp_var_54.unset();
    if (get_function_resolution_cache(FunctionResolutionCacheId{28}) == 0) { get_function_resolution_cache(FunctionResolutionCacheId{28}) = php::fn::function_exists(get_str(241)) ? 1 : 2; }
    tmp_var_56 = get_function_resolution_cache(FunctionResolutionCacheId{28}) == 1 ? get_func(RequestFuncId{10}, get_str(241)) : get_persistent_func(PersistentFuncId{12}, get_str(242));
    if (get_function_resolution_cache(FunctionResolutionCacheId{29}) == 0) { get_function_resolution_cache(FunctionResolutionCacheId{29}) = php::fn::function_exists(get_str(238)) ? 1 : 2; }
    tmp_var_57 = get_function_resolution_cache(FunctionResolutionCacheId{29}) == 1 ? get_func(RequestFuncId{9}, get_str(238)) : get_persistent_func(PersistentFuncId{11}, get_str(239));
    tmp_var_58 = php::call(tmp_var_57, php::VarList{s, 2L, 2L});
    tmp_var_59 = php::toFloat(php::call(tmp_var_56, php::VarList{tmp_var_58}));
    tmp_var_58.unset();
    if (get_function_resolution_cache(FunctionResolutionCacheId{30}) == 0) { get_function_resolution_cache(FunctionResolutionCacheId{30}) = php::fn::function_exists(get_str(241)) ? 1 : 2; }
    tmp_var_60 = get_function_resolution_cache(FunctionResolutionCacheId{30}) == 1 ? get_func(RequestFuncId{10}, get_str(241)) : get_persistent_func(PersistentFuncId{12}, get_str(242));
    if (get_function_resolution_cache(FunctionResolutionCacheId{31}) == 0) { get_function_resolution_cache(FunctionResolutionCacheId{31}) = php::fn::function_exists(get_str(238)) ? 1 : 2; }
    tmp_var_61 = get_function_resolution_cache(FunctionResolutionCacheId{31}) == 1 ? get_func(RequestFuncId{9}, get_str(238)) : get_persistent_func(PersistentFuncId{11}, get_str(239));
    tmp_var_62 = php::call(tmp_var_61, php::VarList{s, 4L, 2L});
    tmp_var_63 = php::toFloat(php::call(tmp_var_60, php::VarList{tmp_var_62}));
    tmp_var_62.unset();
    tmp_var_64 = (php::Array{
        php::Var(tmp_var_55), 
        php::Var(tmp_var_59), 
        php::Var(tmp_var_63), 
        php::Var(a)
    });
    return tmp_var_64;
}


php::Int php_pixelforge__pixelforge__concurrency(php::Object &this_, php::Var n) {
    php::Int tmp_var_0 = 0;
    if (UNEXPECTED(!(n.isNull() || n.isInt()))) {
        php::throwArgumentTypeError(n, get_str(245), 1, get_str(244), get_str(73));
    }

    if (php::toBool(!(php::same(n, php::null)))) {
        php_pixelforge_concurrency(php::toIntArgExact(n, get_str(243), 1, get_str(244)));
    }
    tmp_var_0 = (php::toInt(php_pixelforge_get_concurrency()));
    return tmp_var_0;
}

void php_pixelforge__pixelforge__cache(php::Object &this_, php::Int memoryMb, php::Int files, php::Int items) {
    php_pixelforge_cache(php::toInt(memoryMb), php::toInt(files), php::toInt(items));
}

php::Array php_pixelforge__pixelforge__versions(php::Object &this_) {
    php::Array tmp_var_0;

    tmp_var_0 = (php_pixelforge_versions());
    return tmp_var_0;
}

php::Array php_pixelforge__pixelforge__format(php::Object &this_) {
    php::Array tmp_var_0;

    tmp_var_0 = (php_pixelforge_formats());
    return tmp_var_0;
}

php::Array php_pixelforge__pixelforge__memory(php::Object &this_) {
    php::Array tmp_var_0;

    tmp_var_0 = (php_pixelforge_memory());
    return tmp_var_0;
}


ZEND_METHOD(PixelForge_Image, __construct) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(1, 1, false);
        php::Var arg_handle = php::getCallArg(0);
        php_pixelforge__image____construct(this_, php::takeValue(arg_handle));
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, fromFile) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(1, 2, false);
        php::Var raw_arg_path = php::getCallArg(0);
        if (UNEXPECTED(!(raw_arg_path.isString()))) {
            php::throwArgumentTypeError(raw_arg_path, get_str(246), 1, get_str(247), get_str(203));
        }
        php::Str arg_path = php::toString(raw_arg_path);
        php::Array arg_options = php::toArray(php::getCallArg(1, php_pixelforge__image__fromfile_arg_1_default_value()));
        auto retval = php_pixelforge__image__fromfile(this_, php::takeValue(arg_path),php::takeValue(arg_options));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, fromBuffer) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(1, 2, false);
        php::Var raw_arg_data = php::getCallArg(0);
        if (UNEXPECTED(!(raw_arg_data.isString()))) {
            php::throwArgumentTypeError(raw_arg_data, get_str(248), 1, get_str(204), get_str(203));
        }
        php::Str arg_data = php::toString(raw_arg_data);
        php::Array arg_options = php::toArray(php::getCallArg(1, php_pixelforge__image__frombuffer_arg_1_default_value()));
        auto retval = php_pixelforge__image__frombuffer(this_, php::takeValue(arg_data),php::takeValue(arg_options));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, fromRaw) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(2, 2, false);
        php::Var raw_arg_data = php::getCallArg(0);
        if (UNEXPECTED(!(raw_arg_data.isString()))) {
            php::throwArgumentTypeError(raw_arg_data, get_str(249), 1, get_str(204), get_str(203));
        }
        php::Str arg_data = php::toString(raw_arg_data);
        php::Array arg_raw = php::toArray(php::getCallArg(1));
        auto retval = php_pixelforge__image__fromraw(this_, php::takeValue(arg_data),php::takeValue(arg_raw));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, create) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(1, 1, false);
        php::Array arg_options = php::toArray(php::getCallArg(0));
        auto retval = php_pixelforge__image__create(this_, php::takeValue(arg_options));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, text) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(1, 1, false);
        php::Array arg_options = php::toArray(php::getCallArg(0));
        auto retval = php_pixelforge__image__text(this_, php::takeValue(arg_options));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, join) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(1, 2, false);
        php::Array arg_inputs = php::toArray(php::getCallArg(0));
        php::Array arg_options = php::toArray(php::getCallArg(1, php_pixelforge__image__join_arg_1_default_value()));
        auto retval = php_pixelforge__image__join(this_, php::takeValue(arg_inputs),php::takeValue(arg_options));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, input) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(1, 1, false);
        php::Var arg_in = php::getCallArg(0);
        auto retval = php_pixelforge__image__input(this_, php::takeValue(arg_in));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, limit) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(1, 1, false);
        php::Array arg_options = php::toArray(php::getCallArg(0));
        auto retval = php_pixelforge__image__limit(this_, php::takeValue(arg_options));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, pages) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(1, 1, false);
        php::Array arg_options = php::toArray(php::getCallArg(0));
        auto retval = php_pixelforge__image__pages(this_, php::takeValue(arg_options));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, clone) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 0, false);
        auto retval = php_pixelforge__image__clone(this_);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, handle) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 0, false);
        auto retval = php_pixelforge__image__handle(this_);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, resize) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 3, false);
        php::Var arg_width = php::getCallArg(0, php_pixelforge__image__resize_arg_0_default_value());
        php::Var arg_height = php::getCallArg(1, php_pixelforge__image__resize_arg_1_default_value());
        php::Array arg_options = php::toArray(php::getCallArg(2, php_pixelforge__image__resize_arg_2_default_value()));
        auto retval = php_pixelforge__image__resize(this_, php::takeValue(arg_width),php::takeValue(arg_height),php::takeValue(arg_options));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, extract) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(1, 1, false);
        php::Array arg_region = php::toArray(php::getCallArg(0));
        auto retval = php_pixelforge__image__extract(this_, php::takeValue(arg_region));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, extend) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(1, 1, false);
        php::Var arg_extend = php::getCallArg(0);
        auto retval = php_pixelforge__image__extend(this_, php::takeValue(arg_extend));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, trim) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 1, false);
        php::Array arg_options = php::toArray(php::getCallArg(0, php_pixelforge__image__trim_arg_0_default_value()));
        auto retval = php_pixelforge__image__trim(this_, php::takeValue(arg_options));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, rotate) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 2, false);
        php::Var arg_angle = php::getCallArg(0, php_pixelforge__image__rotate_arg_0_default_value());
        php::Array arg_options = php::toArray(php::getCallArg(1, php_pixelforge__image__rotate_arg_1_default_value()));
        auto retval = php_pixelforge__image__rotate(this_, php::takeValue(arg_angle),php::takeValue(arg_options));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, autoOrient) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 0, false);
        auto retval = php_pixelforge__image__autoorient(this_);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, flip) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 0, false);
        auto retval = php_pixelforge__image__flip(this_);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, flop) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 0, false);
        auto retval = php_pixelforge__image__flop(this_);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, affine) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(1, 2, false);
        php::Array arg_matrix = php::toArray(php::getCallArg(0));
        php::Array arg_options = php::toArray(php::getCallArg(1, php_pixelforge__image__affine_arg_1_default_value()));
        auto retval = php_pixelforge__image__affine(this_, php::takeValue(arg_matrix),php::takeValue(arg_options));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, sharpen) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 1, false);
        php::Array arg_options = php::toArray(php::getCallArg(0, php_pixelforge__image__sharpen_arg_0_default_value()));
        auto retval = php_pixelforge__image__sharpen(this_, php::takeValue(arg_options));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, median) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 1, false);
        php::Var raw_arg_size = php::getCallArg(0, php_pixelforge__image__median_arg_0_default_value());
        if (UNEXPECTED(!(raw_arg_size.isInt()))) {
            php::throwArgumentTypeError(raw_arg_size, get_str(250), 1, get_str(184), get_str(251));
        }
        php::Int arg_size = php::toInt(raw_arg_size);
        auto retval = php_pixelforge__image__median(this_, arg_size);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, blur) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 1, false);
        php::Var arg_sigma = php::getCallArg(0, php_pixelforge__image__blur_arg_0_default_value());
        auto retval = php_pixelforge__image__blur(this_, php::takeValue(arg_sigma));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, flatten) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 1, false);
        php::Array arg_options = php::toArray(php::getCallArg(0, php_pixelforge__image__flatten_arg_0_default_value()));
        auto retval = php_pixelforge__image__flatten(this_, php::takeValue(arg_options));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, unflatten) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 0, false);
        auto retval = php_pixelforge__image__unflatten(this_);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, gamma) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 2, false);
        php::Var raw_arg_gamma = php::getCallArg(0, php_pixelforge__image__gamma_arg_0_default_value());
        if (UNEXPECTED(!((raw_arg_gamma.isFloat() || raw_arg_gamma.isInt())))) {
            php::throwArgumentTypeError(raw_arg_gamma, get_str(110), 1, get_str(252), get_str(253));
        }
        php::Float arg_gamma = php::toFloat(raw_arg_gamma);
        php::Var arg_gammaOut = php::getCallArg(1, php_pixelforge__image__gamma_arg_1_default_value());
        auto retval = php_pixelforge__image__gamma(this_, arg_gamma,php::takeValue(arg_gammaOut));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, negate) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 1, false);
        php::Array arg_options = php::toArray(php::getCallArg(0, php_pixelforge__image__negate_arg_0_default_value()));
        auto retval = php_pixelforge__image__negate(this_, php::takeValue(arg_options));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, normalise) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 1, false);
        php::Array arg_options = php::toArray(php::getCallArg(0, php_pixelforge__image__normalise_arg_0_default_value()));
        auto retval = php_pixelforge__image__normalise(this_, php::takeValue(arg_options));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, normalize) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 1, false);
        php::Array arg_options = php::toArray(php::getCallArg(0, php_pixelforge__image__normalize_arg_0_default_value()));
        auto retval = php_pixelforge__image__normalize(this_, php::takeValue(arg_options));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, clahe) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(1, 1, false);
        php::Array arg_options = php::toArray(php::getCallArg(0));
        auto retval = php_pixelforge__image__clahe(this_, php::takeValue(arg_options));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, threshold) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 2, false);
        php::Var raw_arg_threshold = php::getCallArg(0, php_pixelforge__image__threshold_arg_0_default_value());
        if (UNEXPECTED(!(raw_arg_threshold.isInt()))) {
            php::throwArgumentTypeError(raw_arg_threshold, get_str(254), 1, get_str(83), get_str(251));
        }
        php::Int arg_threshold = php::toInt(raw_arg_threshold);
        php::Array arg_options = php::toArray(php::getCallArg(1, php_pixelforge__image__threshold_arg_1_default_value()));
        auto retval = php_pixelforge__image__threshold(this_, arg_threshold,php::takeValue(arg_options));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, linear) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 2, false);
        php::Var arg_a = php::getCallArg(0, php_pixelforge__image__linear_arg_0_default_value());
        php::Var arg_b = php::getCallArg(1, php_pixelforge__image__linear_arg_1_default_value());
        auto retval = php_pixelforge__image__linear(this_, php::takeValue(arg_a),php::takeValue(arg_b));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, modulate) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(1, 1, false);
        php::Array arg_options = php::toArray(php::getCallArg(0));
        auto retval = php_pixelforge__image__modulate(this_, php::takeValue(arg_options));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, tint) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(1, 1, false);
        php::Var arg_color = php::getCallArg(0);
        auto retval = php_pixelforge__image__tint(this_, php::takeValue(arg_color));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, greyscale) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 1, false);
        php::Var raw_arg_grey = php::getCallArg(0, php_pixelforge__image__greyscale_arg_0_default_value());
        if (UNEXPECTED(!(raw_arg_grey.isBool()))) {
            php::throwArgumentTypeError(raw_arg_grey, get_str(255), 1, get_str(256), get_str(257));
        }
        php::Bool arg_grey = php::toBool(raw_arg_grey);
        auto retval = php_pixelforge__image__greyscale(this_, arg_grey);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, grayscale) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 1, false);
        php::Var raw_arg_grey = php::getCallArg(0, php_pixelforge__image__grayscale_arg_0_default_value());
        if (UNEXPECTED(!(raw_arg_grey.isBool()))) {
            php::throwArgumentTypeError(raw_arg_grey, get_str(258), 1, get_str(256), get_str(257));
        }
        php::Bool arg_grey = php::toBool(raw_arg_grey);
        auto retval = php_pixelforge__image__grayscale(this_, arg_grey);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, toColourspace) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(1, 1, false);
        php::Var raw_arg_space = php::getCallArg(0);
        if (UNEXPECTED(!(raw_arg_space.isString()))) {
            php::throwArgumentTypeError(raw_arg_space, get_str(259), 1, get_str(260), get_str(203));
        }
        php::Str arg_space = php::toString(raw_arg_space);
        auto retval = php_pixelforge__image__tocolourspace(this_, php::takeValue(arg_space));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, toColorspace) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(1, 1, false);
        php::Var raw_arg_space = php::getCallArg(0);
        if (UNEXPECTED(!(raw_arg_space.isString()))) {
            php::throwArgumentTypeError(raw_arg_space, get_str(261), 1, get_str(260), get_str(203));
        }
        php::Str arg_space = php::toString(raw_arg_space);
        auto retval = php_pixelforge__image__tocolorspace(this_, php::takeValue(arg_space));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, removeAlpha) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 0, false);
        auto retval = php_pixelforge__image__removealpha(this_);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, ensureAlpha) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 1, false);
        php::Var raw_arg_alpha = php::getCallArg(0, php_pixelforge__image__ensurealpha_arg_0_default_value());
        if (UNEXPECTED(!((raw_arg_alpha.isFloat() || raw_arg_alpha.isInt())))) {
            php::throwArgumentTypeError(raw_arg_alpha, get_str(262), 1, get_str(112), get_str(253));
        }
        php::Float arg_alpha = php::toFloat(raw_arg_alpha);
        auto retval = php_pixelforge__image__ensurealpha(this_, arg_alpha);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, extractChannel) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(1, 1, false);
        php::Var arg_channel = php::getCallArg(0);
        auto retval = php_pixelforge__image__extractchannel(this_, php::takeValue(arg_channel));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, joinChannel) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(1, 1, false);
        php::Var arg_images = php::getCallArg(0);
        auto retval = php_pixelforge__image__joinchannel(this_, php::takeValue(arg_images));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, bandbool) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(1, 1, false);
        php::Var raw_arg_op = php::getCallArg(0);
        if (UNEXPECTED(!(raw_arg_op.isString()))) {
            php::throwArgumentTypeError(raw_arg_op, get_str(263), 1, get_str(264), get_str(203));
        }
        php::Str arg_op = php::toString(raw_arg_op);
        auto retval = php_pixelforge__image__bandbool(this_, php::takeValue(arg_op));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, boolean) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(2, 2, false);
        php::Var arg_operand = php::getCallArg(0);
        php::Var raw_arg_op = php::getCallArg(1);
        if (UNEXPECTED(!(raw_arg_op.isString()))) {
            php::throwArgumentTypeError(raw_arg_op, get_str(265), 2, get_str(264), get_str(203));
        }
        php::Str arg_op = php::toString(raw_arg_op);
        auto retval = php_pixelforge__image__boolean(this_, php::takeValue(arg_operand),php::takeValue(arg_op));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, dilate) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 1, false);
        php::Var raw_arg_width = php::getCallArg(0, php_pixelforge__image__dilate_arg_0_default_value());
        if (UNEXPECTED(!(raw_arg_width.isInt()))) {
            php::throwArgumentTypeError(raw_arg_width, get_str(266), 1, get_str(10), get_str(251));
        }
        php::Int arg_width = php::toInt(raw_arg_width);
        auto retval = php_pixelforge__image__dilate(this_, arg_width);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, erode) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 1, false);
        php::Var raw_arg_width = php::getCallArg(0, php_pixelforge__image__erode_arg_0_default_value());
        if (UNEXPECTED(!(raw_arg_width.isInt()))) {
            php::throwArgumentTypeError(raw_arg_width, get_str(267), 1, get_str(10), get_str(251));
        }
        php::Int arg_width = php::toInt(raw_arg_width);
        auto retval = php_pixelforge__image__erode(this_, arg_width);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, convolve) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(1, 1, false);
        php::Array arg_kernel = php::toArray(php::getCallArg(0));
        auto retval = php_pixelforge__image__convolve(this_, php::takeValue(arg_kernel));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, recomb) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(1, 1, false);
        php::Array arg_matrix = php::toArray(php::getCallArg(0));
        auto retval = php_pixelforge__image__recomb(this_, php::takeValue(arg_matrix));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, composite) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(1, 1, false);
        php::Array arg_layers = php::toArray(php::getCallArg(0));
        auto retval = php_pixelforge__image__composite(this_, php::takeValue(arg_layers));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, jpeg) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 1, false);
        php::Array arg_o = php::toArray(php::getCallArg(0, php_pixelforge__image__jpeg_arg_0_default_value()));
        auto retval = php_pixelforge__image__jpeg(this_, php::takeValue(arg_o));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, png) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 1, false);
        php::Array arg_o = php::toArray(php::getCallArg(0, php_pixelforge__image__png_arg_0_default_value()));
        auto retval = php_pixelforge__image__png(this_, php::takeValue(arg_o));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, webp) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 1, false);
        php::Array arg_o = php::toArray(php::getCallArg(0, php_pixelforge__image__webp_arg_0_default_value()));
        auto retval = php_pixelforge__image__webp(this_, php::takeValue(arg_o));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, avif) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 1, false);
        php::Array arg_o = php::toArray(php::getCallArg(0, php_pixelforge__image__avif_arg_0_default_value()));
        auto retval = php_pixelforge__image__avif(this_, php::takeValue(arg_o));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, heif) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 1, false);
        php::Array arg_o = php::toArray(php::getCallArg(0, php_pixelforge__image__heif_arg_0_default_value()));
        auto retval = php_pixelforge__image__heif(this_, php::takeValue(arg_o));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, gif) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 1, false);
        php::Array arg_o = php::toArray(php::getCallArg(0, php_pixelforge__image__gif_arg_0_default_value()));
        auto retval = php_pixelforge__image__gif(this_, php::takeValue(arg_o));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, tiff) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 1, false);
        php::Array arg_o = php::toArray(php::getCallArg(0, php_pixelforge__image__tiff_arg_0_default_value()));
        auto retval = php_pixelforge__image__tiff(this_, php::takeValue(arg_o));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, jxl) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 1, false);
        php::Array arg_o = php::toArray(php::getCallArg(0, php_pixelforge__image__jxl_arg_0_default_value()));
        auto retval = php_pixelforge__image__jxl(this_, php::takeValue(arg_o));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, raw) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 0, false);
        auto retval = php_pixelforge__image__raw(this_);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, toFormat) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(1, 2, false);
        php::Var raw_arg_format = php::getCallArg(0);
        if (UNEXPECTED(!(raw_arg_format.isString()))) {
            php::throwArgumentTypeError(raw_arg_format, get_str(268), 1, get_str(206), get_str(203));
        }
        php::Str arg_format = php::toString(raw_arg_format);
        php::Array arg_o = php::toArray(php::getCallArg(1, php_pixelforge__image__toformat_arg_1_default_value()));
        auto retval = php_pixelforge__image__toformat(this_, php::takeValue(arg_format),php::takeValue(arg_o));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, output) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(2, 2, false);
        php::Var raw_arg_format = php::getCallArg(0);
        if (UNEXPECTED(!(raw_arg_format.isString()))) {
            php::throwArgumentTypeError(raw_arg_format, get_str(269), 1, get_str(206), get_str(203));
        }
        php::Str arg_format = php::toString(raw_arg_format);
        php::Array arg_o = php::toArray(php::getCallArg(1));
        auto retval = php_pixelforge__image__output(this_, php::takeValue(arg_format),php::takeValue(arg_o));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, tile) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 1, false);
        php::Array arg_o = php::toArray(php::getCallArg(0, php_pixelforge__image__tile_arg_0_default_value()));
        auto retval = php_pixelforge__image__tile(this_, php::takeValue(arg_o));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, timeout) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(1, 1, false);
        php::Array arg_o = php::toArray(php::getCallArg(0));
        auto retval = php_pixelforge__image__timeout(this_, php::takeValue(arg_o));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, keepMetadata) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 0, false);
        auto retval = php_pixelforge__image__keepmetadata(this_);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, withMetadata) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 0, false);
        auto retval = php_pixelforge__image__withmetadata(this_);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, keepExif) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 0, false);
        auto retval = php_pixelforge__image__keepexif(this_);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, keepIccProfile) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 0, false);
        auto retval = php_pixelforge__image__keepiccprofile(this_);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, withIccProfile) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(1, 1, false);
        php::Var raw_arg_profile = php::getCallArg(0);
        if (UNEXPECTED(!(raw_arg_profile.isString()))) {
            php::throwArgumentTypeError(raw_arg_profile, get_str(270), 1, get_str(271), get_str(203));
        }
        php::Str arg_profile = php::toString(raw_arg_profile);
        auto retval = php_pixelforge__image__withiccprofile(this_, php::takeValue(arg_profile));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, withExif) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(1, 1, false);
        php::Array arg_exif = php::toArray(php::getCallArg(0));
        auto retval = php_pixelforge__image__withexif(this_, php::takeValue(arg_exif));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, withExifMerge) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(1, 1, false);
        php::Array arg_exif = php::toArray(php::getCallArg(0));
        auto retval = php_pixelforge__image__withexifmerge(this_, php::takeValue(arg_exif));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, flattenExif) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(1, 1, false);
        php::Array arg_exif = php::toArray(php::getCallArg(0));
        auto retval = php_pixelforge__image__flattenexif(this_, php::takeValue(arg_exif));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, keepXmp) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 0, false);
        auto retval = php_pixelforge__image__keepxmp(this_);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, keep) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(1, 1, false);
        php::Var raw_arg_flags = php::getCallArg(0);
        if (UNEXPECTED(!(raw_arg_flags.isInt()))) {
            php::throwArgumentTypeError(raw_arg_flags, get_str(272), 1, get_str(273), get_str(251));
        }
        php::Int arg_flags = php::toInt(raw_arg_flags);
        auto retval = php_pixelforge__image__keep(this_, arg_flags);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, toFile) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(1, 1, false);
        php::Var raw_arg_path = php::getCallArg(0);
        if (UNEXPECTED(!(raw_arg_path.isString()))) {
            php::throwArgumentTypeError(raw_arg_path, get_str(274), 1, get_str(247), get_str(203));
        }
        php::Str arg_path = php::toString(raw_arg_path);
        auto retval = php_pixelforge__image__tofile(this_, php::takeValue(arg_path));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, toBuffer) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 1, false);
        php::Var arg_format = php::getCallArg(0, php_pixelforge__image__tobuffer_arg_0_default_value());
        auto retval = php_pixelforge__image__tobuffer(this_, php::takeValue(arg_format));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, toBufferWithInfo) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 1, false);
        php::Var arg_format = php::getCallArg(0, php_pixelforge__image__tobufferwithinfo_arg_0_default_value());
        auto retval = php_pixelforge__image__tobufferwithinfo(this_, php::takeValue(arg_format));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, metadata) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 0, false);
        auto retval = php_pixelforge__image__metadata(this_);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, stats) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 0, false);
        auto retval = php_pixelforge__image__stats(this_);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Image, csv) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(1, 1, false);
        php::Var arg_v = php::getCallArg(0);
        auto retval = php_pixelforge__image__csv(this_, php::takeValue(arg_v));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Gravity, normalise) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(1, 1, false);
        php::Var raw_arg_g = php::getCallArg(0);
        if (UNEXPECTED(!(raw_arg_g.isString()))) {
            php::throwArgumentTypeError(raw_arg_g, get_str(231), 1, get_str(20), get_str(203));
        }
        php::Str arg_g = php::toString(raw_arg_g);
        auto retval = php_pixelforge__gravity__normalise(this_, php::takeValue(arg_g));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_Color, parse) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(1, 1, false);
        php::Var arg_c = php::getCallArg(0);
        auto retval = php_pixelforge__color__parse(this_, php::takeValue(arg_c));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_PixelForge, concurrency) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 1, false);
        php::Var arg_n = php::getCallArg(0, php_pixelforge__pixelforge__concurrency_arg_0_default_value());
        auto retval = php_pixelforge__pixelforge__concurrency(this_, php::takeValue(arg_n));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_PixelForge, cache) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 3, false);
        php::Var raw_arg_memoryMb = php::getCallArg(0, php_pixelforge__pixelforge__cache_arg_0_default_value());
        if (UNEXPECTED(!(raw_arg_memoryMb.isInt()))) {
            php::throwArgumentTypeError(raw_arg_memoryMb, get_str(275), 1, get_str(276), get_str(251));
        }
        php::Int arg_memoryMb = php::toInt(raw_arg_memoryMb);
        php::Var raw_arg_files = php::getCallArg(1, php_pixelforge__pixelforge__cache_arg_1_default_value());
        if (UNEXPECTED(!(raw_arg_files.isInt()))) {
            php::throwArgumentTypeError(raw_arg_files, get_str(275), 2, get_str(277), get_str(251));
        }
        php::Int arg_files = php::toInt(raw_arg_files);
        php::Var raw_arg_items = php::getCallArg(2, php_pixelforge__pixelforge__cache_arg_2_default_value());
        if (UNEXPECTED(!(raw_arg_items.isInt()))) {
            php::throwArgumentTypeError(raw_arg_items, get_str(275), 3, get_str(278), get_str(251));
        }
        php::Int arg_items = php::toInt(raw_arg_items);
        php_pixelforge__pixelforge__cache(this_, arg_memoryMb,arg_files,arg_items);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_PixelForge, versions) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 0, false);
        auto retval = php_pixelforge__pixelforge__versions(this_);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_PixelForge, format) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 0, false);
        auto retval = php_pixelforge__pixelforge__format(this_);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_METHOD(PixelForge_PixelForge, memory) {
    php::Object this_(&execute_data->This);
    PHPX_TRY {
        php::checkCallArgCount(0, 0, false);
        auto retval = php_pixelforge__pixelforge__memory(this_);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}


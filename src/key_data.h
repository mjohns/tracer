#pragma once

#include "key.h"
#include "transform.h"

namespace scad {

// Key positioning data and description of layout and grouping of keys.
struct KeyData {
  KeyData(TransformList origin);

  Key key_plus;
  Key key_1;
  Key key_2;
  Key key_3;
  Key key_4;
  Key key_5;

  Key key_tab;
  Key key_q;
  Key key_w;
  Key key_e;
  Key key_r;
  Key key_t;

  Key key_caps;
  Key key_a;
  Key key_s;
  Key key_d;
  Key key_f;
  Key key_g;

  Key key_shift;
  Key key_z;
  Key key_x;
  Key key_c;
  Key key_v;
  Key key_b;

  Key key_tilde;
  Key key_slash;
  Key key_left_arrow;
  Key key_right_arrow;

  Key key_th1;
  Key key_th2;
  Key key_th3;
  Key key_th_top1;
  Key key_th_top2;
  Key key_th_top3;

  Key key_backspace;
  Key key_delete;
  Key key_alt;
  Key key_ctrl;
  Key key_home;
  Key key_end;

  // clang-format off
  KeyGrid grid {{
    { nullptr,   nullptr,      nullptr,    nullptr,          nullptr,         nullptr},
    { &key_tab,   &key_q,      &key_w,      &key_e,           &key_r,            &key_t},
    { &key_caps, &key_a,      &key_s,      &key_d,           &key_f,            &key_g},
    { nullptr,   &key_z,      &key_x,      &key_c,           &key_v,            &key_b},
    { nullptr,   nullptr,     nullptr,     &key_left_arrow,  nullptr,           nullptr},
  }};
  // clang-format on

  std::vector<Key*> thumb_keys() {
    // return {&key_th1, &key_th2, &key_th3, &key_th_top1, &key_th_top2, &key_th_bottom1};
    return {&key_th1, &key_th2, &key_th3, &key_th_top2, &key_th_top3};
  }

  std::vector<Key*> all_keys() {
    std::vector<Key*> keys;
    for (Key* key : thumb_keys()) {
      keys.push_back(key);
    }
    for (Key* key : grid.keys()) {
      keys.push_back(key);
    }
    return keys;
  }
};

}  // namespace scad

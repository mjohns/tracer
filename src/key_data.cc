#include "key_data.h"

#include <glm/glm.hpp>
#include "key.h"
#include "scad.h"
#include "transform.h"

namespace scad {
namespace {

constexpr double kDefaultKeySpacing = 19;
// The direct distance between switch tops in the bowl.
constexpr double kBowlKeySpacing = 18;

/*
constexpr double kDColumnRadius = 55;
constexpr double kAColumnRadius = 55;
constexpr double kSColumnRadius = 60;
constexpr double kGColumnRadius = 65;
constexpr double kFColumnRadius = 70;
constexpr double kCapsColumnRadius = 60;
*/
constexpr double kDColumnRadius = 70;
constexpr double kAColumnRadius = 70;
constexpr double kSColumnRadius = 70;
constexpr double kGColumnRadius = 70;
constexpr double kFColumnRadius = 70;
constexpr double kCapsColumnRadius = 70;

// Rotates a key about the x axis until it has traveled the direct distance (not on the arc).
Key GetRotatedKey(double radius, bool up) {
  double distance = kBowlKeySpacing;
  double rotation_direction = up ? 1.0 : -1.0;
  double degrees = 1;

  // Use precomputed numbers for known radiuses to speed up execution.
  if (radius == 50) {
    degrees = 20.740;
  }
  if (radius == 55) {
    degrees = 18.840;
  }
  if (radius == 60) {
    degrees = 17.26;
  }
  if (radius == 65) {
    degrees = 15.920;
  }
  if (radius == 70) {
    degrees = 14.780;
  }

  bool is_first = true;
  while (true) {
    Key k;
    k.local_transforms.TranslateZ(-1 * radius)
        .RotateX(rotation_direction * degrees)
        .TranslateZ(radius);
    glm::vec3 point = k.GetTransforms().Apply(kOrigin);
    float current_distance = glm::length(point);
    if (current_distance > distance) {
      if (!is_first) {
        printf("Cumputed degrees %.3f for radius %.3f\n", degrees, radius);
      }
      return k;
    }
    degrees += .01;
    is_first = false;
  }
}

Key GetRotatedKeyUp(double radius) {
  return GetRotatedKey(radius, true);
}

Key GetRotatedKeyDown(double radius) {
  return GetRotatedKey(radius, false);
}

}  // namespace

KeyData::KeyData(TransformList key_origin) {
  //
  // Thumb keys
  //

  key_th1.Configure([&](Key& k) {
    k.name = "key_th1";
    k.SetParent(key_origin);
    k.SetPosition(60, -9.18, 42.83);
    k.t().x += -8;
    k.t().y += 3;
    k.t().z += 1.5;

    k.t().rx = 14;
    k.t().ry = 22;
    k.AddTransform();
    k.t().rz = -9;
  });

  key_th2.Configure([&](Key& k) {
    k.name = "key_th2";
    k.SetParent(key_th1);
    k.SetPosition(19 + 1, -1, 2);
  });

  key_th3.Configure([&](Key& k) {
    k.name = "key_th3";
    k.SetParent(key_th2);
    k.SetPosition(19, -7, 1);
    //k.t().ry = -18;
    k.t().y -= 3;
  });


  key_th_bottom2.Configure([&](Key& k) {
    k.name = "key_th_bottom_2";
    k.SetParent(key_th3);
    //k.SetPosition(-5, -20, -9.5);
    //k.SetPosition(0, -23, -8);
    k.SetPosition(-15, -17, -2);
    k.t().rz = -35;
  });

  key_th_top2.Configure([&](Key& k) {
    k.name = "key_th_top2";
    // k.type = KeyType::SA;
    k.SetParent(key_th2);
    k.SetPosition(0, 19, 3);
    // k.t().x += -1;
    // k.t().y += 4;
    // k.t().rz = -7;
    // k.t().rx = 15;
    // k.t().ry = -18;
    k.t().x += 6;
    k.t().z += 2;
    k.t().rx = 10;
    k.t().ry = -10;
    // k.t().y += -2;
  });

  key_th_top3.Configure([&](Key& k) {
    k.name = "key_th_top3";
    // k.type = KeyType::SA;
    k.SetParent(key_th3);
    k.SetPosition(0, 19, 3);
    // k.t().x += -1;
    // k.t().y += 4;
    // k.t().rz = -7;
    // k.t().ry = -18;
    k.t().x += 6.3;
    k.t().rx = 10;
    k.t().ry = -15;
    // k.t().y += -2;
    k.AddTransform();
    //k.t().z = 2.5;
    k.t().z = 3.7;
  });


  //
  // Main bowl keys
  //

  // All keys in the dish are relative to d and then based off of their
  // associated key in the home row.
  key_d.Configure([&](Key& k) {
    k.name = "d";
    k.SetParent(key_origin);
    k.SetPosition(26.40, 50.32, 17.87);
    k.t().ry = -15;
    k.t().z += 5;
    k.t().x += -1;
    k.t().y += .5;
  });

  key_f.Configure([&](Key& k) {
    k.name = "f";

    // Absolute:
    // k.SetPosition(44.3, 49.37, 28.1);
    // k.t().ry = -20;

    k.SetParent(key_d);
    k.SetPosition(19.938, -0.950, 5.249);
    k.t().ry = -5;
    k.t().y += -2;
  });

  key_g.Configure([&](Key& k) {
    k.name = "g";

    k.SetParent(key_f);
    k.SetPosition(18.65, -1.310, 3.305);
    k.t().ry = -5;

    k.t().z += -2.3;
    k.t().x += 1;
    k.t().y += 1.5;
  });

  key_s.Configure([&](Key& k) {
    k.name = "s";

    // Absolute:
    // k.SetPosition(6.09, 50.23, 18.05);
    // k.t().ry = -10;

    k.SetParent(key_d);
    k.SetPosition(-19.571, -0.090, 5.430);
    k.t().ry = 5;

    k.t().y += -2.5;
    k.t().z += -.5;
  });

  key_a.Configure([&](Key& k) {
    k.name = "a";

    // Absolute:
    // k.SetPosition(-15.41, 44.06, 19.7);
    // k.t().ry = -10;

    k.SetParent(key_s);
    k.SetPosition(-20.887, -6.170, 5.358);

    k.t().y += -6;
    k.t().ry = 3;
    //k.t().z += -2;
    k.t().x += 0;
  });

  key_caps.Configure([&](Key& k) {
    k.name = "caps";

    // Absolute:
    // k.SetPosition(-37.7, 48.06, 15.98);
    // k.t().ry = -5;

    k.SetParent(key_a);
    k.SetPosition(-22.597, 0.000, 0.207);
    k.t().ry = 10;
    k.t().z += 3;
    k.t().y += 3;
  });

  // D Column
  key_e = GetRotatedKey(kDColumnRadius, true);
  key_e.Configure([&](Key& k) {
    k.name = "e";
    k.SetParent(key_d);

    k.AddTransform();
   // k.t().z = 2;
  });

  // This key is different from the others in the column. It should be less angled due to the larger
  // radius.
  key_3 = GetRotatedKey(kDColumnRadius, true);
  key_3.Configure([&](Key& k) {
    k.name = "3";
    k.SetParent(key_e);

    k.AddTransform();
    k.t().z = 1;
  });

  key_c = GetRotatedKey(kDColumnRadius, false);
  key_c.Configure([&](Key& k) {
    k.name = "c";
    k.SetParent(key_d);
  });

  key_left_arrow = GetRotatedKey(kDColumnRadius, false);
  key_left_arrow.Configure([&](Key& k) {
    k.name = "left_arrow";
    k.SetParent(key_c);
  });

  // S column
  key_w = GetRotatedKey(kSColumnRadius, true);
  key_w.Configure([&](Key& k) {
    k.name = "w";
    k.SetParent(key_s);

    k.AddTransform();
  //  k.t().z = 2.6;
  });

  /*

  key_w2;
  key_w2.Configure([&](Key& k) {
    k.name = "w2";
    k.SetParent(key_w2);
    k.SetPosition(j
  });
  */

  key_2 = GetRotatedKey(kSColumnRadius, true);
  key_2.Configure([&](Key& k) {
    k.name = "2";
    k.SetParent(key_w);

    k.AddTransform();
    k.t().z = 1;
  });

  key_x = GetRotatedKey(kSColumnRadius, false);
  key_x.Configure([&](Key& k) {
    k.name = "x";
    k.SetParent(key_s);
  });

  key_slash = GetRotatedKey(kSColumnRadius, false);
  key_slash.Configure([&](Key& k) {
    k.name = "slash";
    k.SetParent(key_x);
  });

  // F column
  key_r = GetRotatedKey(kFColumnRadius, true);
  key_r.Configure([&](Key& k) {
    k.name = "r";
    k.SetParent(key_f);

    k.AddTransform();
  //  k.t().z = 1.7;
  });

  key_4 = GetRotatedKey(kFColumnRadius, true);
  key_4.Configure([&](Key& k) {
    k.name = "4";
    k.SetParent(key_r);

    k.AddTransform();
    k.t().z = 1;
  });

  key_v = GetRotatedKey(kFColumnRadius, false);
  key_v.Configure([&](Key& k) {
    k.name = "v";
    k.SetParent(key_f);
  });

  key_right_arrow = GetRotatedKey(kFColumnRadius, false);
  key_right_arrow.Configure([&](Key& k) {
    k.name = "right_arrow";
    k.SetParent(key_v);
  });

  key_t = GetRotatedKey(kGColumnRadius, true);
  key_t.Configure([&](Key& k) {
    k.name = "t";
    k.SetParent(key_g);

    k.AddTransform();
  });

  key_5 = GetRotatedKey(kGColumnRadius, true);
  key_5.Configure([&](Key& k) {
    k.name = "5";
    k.SetParent(key_t);
    // 5 hits 4 a little.
    k.t().x = 1.5;
  });

  key_b = GetRotatedKey(kGColumnRadius, false);
  key_b.Configure([&](Key& k) {
    k.name = "b";
    k.SetParent(key_g);
  });

  // A column
  key_q = GetRotatedKey(70, true);
  key_q.Configure([&](Key& k) {
    k.name = "q";
    k.SetParent(key_a);

    k.AddTransform();
    k.t().y = 3;
    k.t().z = -2;

    k.t().y += 1;
    k.t().z += -2;
  });

  key_1 = GetRotatedKey(kAColumnRadius, true);
  key_1.Configure([&](Key& k) {
    k.name = "1";
    k.SetParent(key_q);
  });

  key_z = GetRotatedKey(kAColumnRadius, false);
  key_z.Configure([&](Key& k) {
    k.name = "z";
    k.SetParent(key_a);
  });

  key_tilde = GetRotatedKey(kAColumnRadius, false);
  key_tilde.Configure([&](Key& k) {
    k.name = "tilde";
    k.SetParent(key_z);
  });

  // Caps column
  // key_tab = GetRotatedKey(kCapsColumnRadius, true);
  key_tab.Configure([&](Key& k) {
    k.name = "tab";
    k.SetParent(key_w);
    k.SetPosition(-18.5 - 2.7, -.4, 3);
    k.SetPosition(-18.5 - 2.7, 2.5, 5);
    k.t().ry = 10;
  });

  key_plus = GetRotatedKey(kCapsColumnRadius, true);
  key_plus.Configure([&](Key& k) {
    k.name = "plus";
    k.SetParent(key_tab);
  });

  key_shift = GetRotatedKey(kCapsColumnRadius, false);
  key_shift.Configure([&](Key& k) {
    k.name = "shift";
    k.SetParent(key_caps);
  });

}

}  // namespace scad


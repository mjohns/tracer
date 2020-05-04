#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "key.h"
#include "key_data.h"
#include "scad.h"
#include "transform.h"

using namespace scad;

constexpr bool kWriteTestKeys = false;
constexpr bool kIncludeDactylRef = false;
// Add the caps into the stl for testing.
constexpr bool kAddCaps = false;

enum class Direction { UP, DOWN, LEFT, RIGHT };

void AddShapes(std::vector<Shape>* shapes, std::vector<Shape> to_add) {
  for (Shape s : to_add) {
    shapes->push_back(s);
  }
}

Shape ConnectMainKeys(KeyData& d);

int main() {
  printf("generating..\n");
  TransformList key_origin;
  //  key_origin.RotateY(10);
  key_origin.Translate(-20, -40, 3);

  // This is where all of the logic to position the keys is done. Everything below is cosmetic
  // trying to build the case.
  KeyData d(key_origin);

  if (kWriteTestKeys) {
    std::vector<Shape> test_shapes;
    std::vector<Key*> test_keys = {
        //&d.key_th1, &d.key_th2, &d.key_th3, &d.key_th_top3, &d.key_th_top2,
        &d.key_th1,
        &d.key_th2,
        &d.key_th3,
        &d.key_th_top2,
        &d.key_th_top3,
        //   &d.key_d,
    };
    // &d.key_q, &d.key_w, &d.key_f, &d.key_3, &d.key_tab};
    // test_keys = d.all_keys();
    for (Key* key : test_keys) {
      key->add_side_nub = false;
      key->extra_z = 4;
      test_shapes.push_back(key->GetSwitch());
      if (kAddCaps) {
        test_shapes.push_back(key->GetCap().Color("red"));
      }
    }
    if (kIncludeDactylRef) {
      Shape dactyl_manuform = Import("dactyl_manuform.stl").Translate(9, 8, -3.5);
      Shape dactyl_cc = Import("dactyl_cc.stl");
      test_shapes.push_back(dactyl_manuform.Color("green", .6));
      //  test_shapes.push_back(dactyl_cc.Color("blue", .3));
    }
    UnionAll(test_shapes).Subtract(d.key_th_top2.GetInverseCap()).WriteToFile("test_keys.scad");
    return 0;
  }

  // Set all of the widths here. This must be done before calling any of GetTopLeft etc.

  d.key_q.extra_z = 2;

  // d.key_b.extra_width_bottom = 3;
  d.key_th1.extra_width_top = 4;
  d.key_th1.extra_width_left = 2;
  d.key_th2.extra_width_bottom = 6;
  d.key_th_top3.extra_width_top = 4;
  d.key_th3.extra_width_right = 2;

  std::vector<Shape> shapes;

  shapes.push_back(
      Union(Tri(d.key_caps.GetTopRight(), d.key_a.GetTopLeft(), d.key_q.GetBottomLeft()),
            TriFan(d.key_q.GetTopLeft(),
                   {
                       d.key_q.GetBottomLeft(),
                       d.key_caps.GetTopRight(),
                       d.key_caps.GetTopLeft(),
                       d.key_tab.GetTopLeft(),
                       d.key_tab.GetBottomLeft(),
                       d.key_q.GetTopRight(),
                   })));
  shapes.push_back(TriFan(d.key_q.GetTopRight(),
                          {
                              d.key_tab.GetBottomLeft(),
                              d.key_tab.GetBottomRight(),
                          }));

  shapes.push_back(TriFan(d.key_z.GetTopLeft(),
                          {
                              d.key_a.GetBottomLeft(),
                              d.key_caps.GetBottomRight(),
                              d.key_caps.GetBottomLeft(),
                              d.key_z.GetBottomLeft(),
                          }));
  shapes.push_back(TriFan(d.key_s.GetTopLeft(),
                          {
                              d.key_w.GetBottomLeft(),
                              d.key_tab.GetBottomRight(),
                              d.key_q.GetTopRight(),
                              d.key_q.GetBottomRight(),
                              d.key_s.GetBottomLeft(),
                          }));

  shapes.push_back(TriFan(d.key_x.GetTopLeft(),
                          {
                              d.key_s.GetBottomLeft(),
                              d.key_q.GetBottomRight(),
                              d.key_a.GetTopRight(),
                              d.key_a.GetBottomRight(),
                              d.key_x.GetBottomLeft(),
                          }));
  shapes.push_back(TriFan(d.key_z.GetTopRight(),
                          {
                              d.key_a.GetBottomRight(),
                              d.key_x.GetBottomLeft(),
                              d.key_x.GetBottomRight(),
                              // d.key_c.GetBottomLeft(),
                              d.key_left_arrow.GetTopLeft(),
                              d.key_left_arrow.GetBottomLeft(),
                              d.key_z.GetBottomRight(),
                          }));
  shapes.push_back(TriFan(d.key_c.GetBottomLeft(),
                          {
                              d.key_x.GetBottomRight(),
                              d.key_left_arrow.GetTopLeft(),
                          }));
  shapes.push_back(TriFan(d.key_c.GetBottomLeft(),
                          {
                              d.key_x.GetBottomRight(),
                              d.key_left_arrow.GetTopLeft(),
                          }));

  shapes.push_back(TriFan(d.key_b.GetBottomLeft(),
                          {
                              d.key_th_top2.GetTopLeft(),
                              d.key_th_top2.GetBottomLeft(),
                              d.key_th2.GetTopLeft(),
                              d.key_v.GetBottomRight(),
                          }));
  shapes.push_back(TriFan(d.key_v.GetBottomLeft(),
                          {
                              d.key_v.GetBottomRight(),
                              d.key_th2.GetTopLeft(),
                              d.key_left_arrow.GetBottomRight(),
                              d.key_left_arrow.GetTopRight(),
                              d.key_c.GetBottomRight(),
                          }));
  shapes.push_back(TriFan(d.key_th2.GetBottomLeft(),
                          {
                              d.key_th1.GetBottomRight(),
                              d.key_th1.GetTopRight(),
                              // d.key_left_arrow.GetBottomRight(),
                              d.key_th2.GetTopLeft(),
                          }));
  shapes.push_back(TriFan(d.key_th1.GetTopLeft(),
                          {
                              d.key_left_arrow.GetBottomRight(),
                              d.key_th2.GetTopLeft(),
                              d.key_th1.GetTopRight(),
                          }));

  shapes.push_back(TriFan(d.key_th1.GetTopLeft(),
                          {
                              d.key_left_arrow.GetBottomRight(),
                              d.key_th2.GetTopLeft(),
                              d.key_th1.GetTopRight(),
                          }));
  shapes.push_back(TriFan(d.key_th1.GetTopLeft(),
                          {
                              d.key_left_arrow.GetBottomRight(),
                              d.key_th2.GetTopLeft(),
                              d.key_th1.GetTopRight(),
                          }));
  shapes.push_back(TriFan(
      d.key_left_arrow.GetBottomLeft(),
      {
          d.key_left_arrow.GetBottomRight(), d.key_th1.GetTopLeft(), d.key_th1.GetBottomLeft(),
          // connect more around?
      }));
  shapes.push_back(TriFan(d.key_th_top2.GetTopRight(),
                          {
                              d.key_th_top2.GetTopLeft(),
                              d.key_b.GetBottomRight(),
                              d.key_b.GetTopRight(),
                          }));
  shapes.push_back(TriFan(d.key_th_top2.GetTopRight(),
                          {
                              d.key_th_top3.GetTopLeft(),
                              d.key_th_top3.GetTopRight(),
                          }));

  shapes.push_back(TriFan(d.key_th_top3.GetBottomRight(),
                          {
                              d.key_th3.GetTopRight(),
                              d.key_th3.GetBottomRight(),
                          }));

  //
  // Thumb plate
  //

  shapes.push_back(ConnectMainKeys(d));
  shapes.push_back(Union(ConnectVertical(d.key_q, d.key_a),
                         ConnectVertical(d.key_a, d.key_z),
                         ConnectHorizontal(d.key_caps, d.key_a),
                         ConnectHorizontal(d.key_th2, d.key_th3),
                         ConnectHorizontal(d.key_th_top2, d.key_th_top3),
                         ConnectVertical(d.key_th_top2, d.key_th2),
                         ConnectVertical(d.key_th_top3, d.key_th3),
                         ConnectDiagonal(d.key_th_top2, d.key_th_top3, d.key_th3, d.key_th2),
                         // ConnectHorizontal(d.key_a, d.key_x),
                         ConnectHorizontal(d.key_tab, d.key_w)));

  //
  // Make the wall
  //
  {
    struct WallPoint {
      WallPoint(TransformList transforms,
                Direction out_direction,
                float extra_distance = 0,
                float extra_width = 0)
          : transforms(transforms),
            out_direction(out_direction),
            extra_distance(extra_distance),
            extra_width(extra_width) {
      }
      TransformList transforms;
      Direction out_direction;
      float extra_distance;
      float extra_width;
    };

    Direction up = Direction::UP;
    Direction down = Direction::DOWN;
    Direction left = Direction::LEFT;
    Direction right = Direction::RIGHT;

    std::vector<WallPoint> wall_points = {
        // Start top left and go clockwise
        {d.key_tab.GetTopLeft(), up},
        {d.key_tab.GetTopRight(), up},

        {d.key_w.GetTopLeft(), up},
        {d.key_w.GetTopRight(), up},

        {d.key_e.GetTopLeft(), up},
        {d.key_e.GetTopRight(), up},

        {d.key_r.GetTopLeft(), up},
        {d.key_r.GetTopRight(), up},

        {d.key_t.GetTopLeft(), up},
        {d.key_t.GetTopRight(), up},
        {d.key_t.GetTopRight(), right},
        {d.key_t.GetBottomRight(), right},

        {d.key_g.GetTopRight(), right},
        {d.key_g.GetBottomRight(), right},

        {d.key_b.GetTopRight(), right},

        {d.key_th_top2.GetTopRight().RotateFront(0, 0, -20), up, 0, 0},

        {d.key_th_top3.GetTopRight(), up},
        {d.key_th_top3.GetTopRight(), right},
        {d.key_th_top3.GetBottomRight(), right},

        {d.key_th3.GetBottomRight(), right},
        {d.key_th3.GetBottomRight(), down},
        {d.key_th3.GetBottomLeft(), down},

        {d.key_th2.GetBottomRight(), down},
        {d.key_th2.GetBottomLeft(), down},

        {d.key_th1.GetBottomRight(), down},
        {d.key_th1.GetBottomLeft(), down},

        {d.key_left_arrow.GetBottomLeft().RotateFront(0, 0, -20), down, 0, 1},

        {d.key_z.GetBottomRight(), down},
        {d.key_z.GetBottomLeft(), down},
        {d.key_z.GetBottomLeft(), left},

        {d.key_caps.GetBottomLeft(), left},
        {d.key_caps.GetTopLeft(), left},

        {d.key_tab.GetTopLeft(), left},

        //{d.key_1.GetTopRight().RotateFront(0, 0, 30), up, 0, 1},

    };

    std::vector<std::vector<Shape>> wall_slices;
    for (WallPoint point : wall_points) {
      Shape s1 = point.transforms.Apply(GetPostConnector());

      TransformList t = point.transforms;
      glm::vec3 out_dir;
      float distance = 4.8 + point.extra_distance;
      switch (point.out_direction) {
        case Direction::UP:
          t.AppendFront(TransformList().Translate(0, distance, 0).RotateX(-20));
          break;
        case Direction::DOWN:
          t.AppendFront(TransformList().Translate(0, -1 * distance, 0).RotateX(20));
          break;
        case Direction::LEFT:
          t.AppendFront(TransformList().Translate(-1 * distance, 0, 0).RotateY(-20));
          break;
        case Direction::RIGHT:
          t.AppendFront(TransformList().Translate(distance, 0, 0).RotateY(20));
          break;
      }

      // Make sure the section extruded to the bottom is thick enough. With certain angles the
      // projection is very small if you just use the post connector from the transform. Compute
      // an explicit shape.
      const glm::vec3 post_offset(0, 0, -4);
      const glm::vec3 p = point.transforms.Apply(post_offset);
      const glm::vec3 p2 = t.Apply(post_offset);

      glm::vec3 out_v = p2 - p;
      out_v.z = 0;
      const glm::vec3 in_v = -1.f * glm::normalize(out_v);

      float width = 3.3 + point.extra_width;
      Shape s2 = Hull(Cube(.1).Translate(p2), Cube(.1).Translate(p2 + (width * in_v)));

      std::vector<Shape> slice;
      slice.push_back(Hull(s1, s2));
      slice.push_back(Hull(s2, s2.Projection().LinearExtrude(.1).TranslateZ(.05)));

      wall_slices.push_back(slice);
    }

    for (size_t i = 0; i < wall_slices.size(); ++i) {
      auto& slice = wall_slices[i];
      auto& next_slice = wall_slices[(i + 1) % wall_slices.size()];
      for (size_t j = 0; j < slice.size(); ++j) {
        shapes.push_back(Hull(slice[j], next_slice[j]));
        // Uncomment for testing. Much faster and easier to visualize.
        // shapes.push_back(slice[j]);
      }
    }
  }

  for (Key* key : d.all_keys()) {
    shapes.push_back(key->GetSwitch());
    if (kAddCaps) {
      shapes.push_back(key->GetCap().Color("red"));
    }
  }

  // Add all the screw inserts.
  std::vector<Shape> screw_holes;
  {
    double screw_height = 5;
    double screw_radius = 4.4 / 2.0;
    Shape screw_hole = Cylinder(screw_height + 2, screw_radius, 30);
    Shape screw_insert =
        Cylinder(screw_height, screw_radius + 1.65, 30).TranslateZ(screw_height / 2);

    glm::vec3 screw_left_bottom = d.key_shift.GetBottomLeft().Apply(kOrigin);
    screw_left_bottom.z = 0;
    screw_left_bottom.x += 3.2;

    glm::vec3 screw_left_top = d.key_plus.GetTopLeft().Apply(kOrigin);
    screw_left_top.z = 0;
    screw_left_top.x += 2.8;
    screw_left_top.y += -.5;

    glm::vec3 screw_right_top = d.key_5.GetTopRight().Apply(kOrigin);
    screw_right_top.z = 0;
    screw_right_top.x -= .8;
    screw_right_top.y += -.5;

    glm::vec3 screw_right_bottom = d.key_end.GetBottomLeft().Apply(kOrigin);
    screw_right_bottom.z = 0;
    screw_right_bottom.y += 3.5;
    screw_right_bottom.x += 1.5;

    glm::vec3 screw_right_mid = d.key_ctrl.GetTopLeft().Apply(kOrigin);
    screw_right_mid.z = 0;
    screw_right_mid.y += -.9;

    /*
    shapes.push_back(Union(screw_insert.Translate(screw_left_top),
                           screw_insert.Translate(screw_right_top),
                           screw_insert.Translate(screw_right_mid),
                           screw_insert.Translate(screw_right_bottom),
                           screw_insert.Translate(screw_left_bottom)));
                           */
    screw_holes = {
        screw_hole.Translate(screw_left_top),
        screw_hole.Translate(screw_right_top),
        screw_hole.Translate(screw_right_mid),
        screw_hole.Translate(screw_right_bottom),
        screw_hole.Translate(screw_left_bottom),
    };
  }

  std::vector<Shape> negative_shapes;
  // AddShapes(&negative_shapes, screw_holes);
  // Cut off the parts sticking up into the thumb plate.

  // Cut out holes for cords. Inserts can be printed to fit in.
  Shape connector_hole = Cube(10, 20, 10).TranslateZ(12 / 2);
  glm::vec3 connector_location1 = d.key_4.GetTopLeft().Apply(kOrigin);
  connector_location1.z = 6;
  connector_location1.x += 9.75;
  glm::vec3 connector_location2 = d.key_5.GetTopLeft().Apply(kOrigin);
  connector_location2.z = 6;
  connector_location2.x += 10.5;
  negative_shapes.push_back(connector_hole.Translate(connector_location1));
  negative_shapes.push_back(connector_hole.Translate(connector_location2));

  Shape result = UnionAll(shapes);
  // Subtracting is expensive to preview and is best to disable while testing.
  result = result.Subtract(UnionAll(negative_shapes));
  result.WriteToFile("v1_left.scad");
  result.MirrorX().WriteToFile("v1_right.scad");

  {
    double depth = 13;
    double width = 15;
    double top_width = width;
    double mid_width = 6;
    double mid_height = 5.75;
    // Height of the bottom plate on the trrs jack.
    double bottom_plate_height = 2;

    Shape bottom_plate =
        Cube(width, 2, depth).TranslateY(-1 - bottom_plate_height).TranslateZ(depth / 2);
    Shape bottom_face = Cube(width, 5, 2).Translate(0, -(5 / 2 + 3), 1);
    Shape top_face = Cube(top_width, 5, 2).Translate(0, 5 / 2 + mid_height + 1, 1);

    Shape top_plate = Cube(top_width, 2, depth).TranslateY(1 + mid_height).TranslateZ(depth / 2);
    double back_height = mid_height + 6;
    Shape back_plate = Cube(top_width, back_height, 2).Translate(0, back_height / 2 - 4, 1 + depth);

    Union(top_face, bottom_plate, bottom_face, top_plate, back_plate).WriteToFile("trrs.scad");
  }

  // Bottom plate
  {
    std::vector<Shape> bottom_plate_shapes = {result};
    for (Key* key : d.all_keys()) {
      bottom_plate_shapes.push_back(Hull(key->GetSwitch()));
    }

    Shape bottom_plate = UnionAll(bottom_plate_shapes)
                             .Projection()
                             .LinearExtrude(1.5)
                             .Subtract(UnionAll(screw_holes));
    bottom_plate.WriteToFile("v1_bottom_left.scad");
    bottom_plate.MirrorX().WriteToFile("v1_bottom_right.scad");
  }

  return 0;
}

Shape ConnectMainKeys(KeyData& d) {
  std::vector<Shape> shapes;
  for (int r = 0; r < d.grid.num_rows(); ++r) {
    for (int c = 2; c < d.grid.num_columns(); ++c) {
      Key* key = d.grid.get_key(r, c);
      if (!key) {
        // No key at this location.
        continue;
      }
      Key* left = d.grid.get_key(r, c - 1);
      if (c == 2) {
        left = nullptr;
      }
      Key* top_left = d.grid.get_key(r - 1, c - 1);
      Key* top = d.grid.get_key(r - 1, c);

      if (left) {
        shapes.push_back(ConnectHorizontal(*left, *key));
      }
      if (top) {
        shapes.push_back(ConnectVertical(*top, *key));
        if (left && top_left) {
          shapes.push_back(ConnectDiagonal(*top_left, *top, *key, *left));
        }
      }
    }
  }
  return UnionAll(shapes);
}

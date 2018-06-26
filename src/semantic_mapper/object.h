#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/common/transforms.h>
#include <pcl/common/norms.h>
#include <pcl/filters/voxel_grid.h>

typedef pcl::PointXYZRGB Point;
typedef pcl::PointCloud<Point> PointCloud;

class Object;
typedef std::shared_ptr<Object> ObjectPtr;
typedef std::vector<ObjectPtr> ObjectPtrVector;
typedef std::map<ObjectPtr,int> ObjectPtrIdMap;
typedef std::set<Object> ObjectSet;

//this class is a container for a 3d object that composes the semantic map
class Object {
  public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    //constructor
    Object(const std::string &model_="",
           const Eigen::Vector3f &position_=Eigen::Vector3f::Identity(),
           const Eigen::Vector3f &min_=Eigen::Vector3f::Zero(),
           const Eigen::Vector3f &max_=Eigen::Vector3f::Zero(),
           const Eigen::Vector3f &color_=Eigen::Vector3f::Zero(),
           const PointCloud::Ptr &cloud_=0);


    bool operator < (const Object &o) const;
    bool operator == (const Object &o) const;


    //setters and getters
    inline const std::string& model() const {return _model;}
    inline std::string& model() {return _model;}
    inline const Eigen::Vector3f& position() const {return _position;}
    inline Eigen::Vector3f& position() {return _position;}
    inline const Eigen::Vector3f& min() const {return _min;}
    inline Eigen::Vector3f& min() {return _min;}
    inline const Eigen::Vector3f& max() const {return _max;}
    inline Eigen::Vector3f& max() {return _max;}
    inline const Eigen::Vector3f &color() const {return _color;}
    inline Eigen::Vector3f &color() {return _color;}
    inline const PointCloud::Ptr &cloud() const {return _cloud;}
    inline PointCloud::Ptr &cloud() {return _cloud;}

    //merge two objects
    void merge(const ObjectPtr &o);

  private:

    std::string _model;

    Eigen::Vector3f _position;

    //lower vertex of the object bounding box
    Eigen::Vector3f _min;

    //upper vertex of the object bounding box
    Eigen::Vector3f _max;

    //object color (for visualization only)
    Eigen::Vector3f _color;

    //object point cloud
    PointCloud::Ptr _cloud;

    pcl::VoxelGrid<Point> _voxelizer;
};

#pragma once
#include <Windows.h>
#include <osg/NodeVisitor>
#include <osg/Matrix>
#include <osg/Geometry>
#include <osg/Transform>
#include <osg/Texture2D>
#include <osg/MatrixTransform>
#include <osgUtil/Export>
#include <map>
#include <set>
#include <osg/Geode>
#include <osgDB/WriteFile>
#include <osgDB/ReadFile>
#include <osg/PagedLOD>
#include <osg/ComputeBoundsVisitor>
#include "json/json.h"
#include <string>
#include <sstream>
#include "OSG2GLTF.h"
#include "EllipsoidModel.h"
//��PagedLOD��OSG�����ڵ㵽3D Tile��ת����
class PagedLOD2Tiles
{
public:
	//�Ƿ��Z�ᳯ�Ϸ�תΪY���ϣ�Ĭ��ΪTRUE
	bool m_flipAxis;
	//ģ�;ֲ�����ϵ���б任�ľ���
	osg::Matrix m_localTransform;
	PagedLOD2Tiles();
	~PagedLOD2Tiles();
	//�Ѵ�PagedLOD��osg�ڵ��ļ�ת��Ϊ3D Tile
	//outdir:����ļ���·��
	void toTileSet(std::string pagelodfile,  std::string outdir);
	//�Ѵ�PagedLOD��osg�ڵ�ת��Ϊ3D Tile
	//outdir:����ļ���·��
	void toTileSet(osg::Node* node, std::string outdir);
	//�Ѵ�PagedLOD��osg�ڵ�ת��Ϊ3D Tile��group�ڵ㱾�����������ݣ�����������PagedLOD�ӽڵ㣬���group�����һ��û��content��3D Tile�ڵ㡣
	//outdir:����ļ���·��
	void toTileSet(osg::Group* group, std::string outdir);
	//���õ�������;ֲ�ת������
	//lat:γ��
	//lon:����
	//height:�߶� �������Ǿ��Ժ��θ߶ȣ�
	//localTransform��ģ�;ֲ�����ϵ���б任�ľ���
	void setTransform(double lat,double lon, double height,osg::Matrix localTransform = osg::Matrix::identity());

private:
	osg::CesiumEllipsoidModel m_ellipsoidModel;
	osg::Matrixd m_local2world;
	osg::Vec3d m_latlonheight;
private:
	Json::Value createTransformNode(osg::Matrixd& mat);
	Json::Value createBoxNode(osg::BoundingBox bb);
	Json::Value createRegionNode(osg::BoundingBoxd localbb);
	osg::BoundingBox flip(osg::BoundingBox bb);
	//����3D Tile��Geometric error����ֵ
	//Ŀǰֻ֧��PIXEL_SIZE_ON_SCREENģʽ��range
	float calGeometricError(float radius, float screenPixels);
	void findPagedLOD(osg::Node* parent, std::vector<osg::PagedLOD*>& pagedLODList);
	int createNode(std::string filename,osg::Node* node2, std::string outname,std::string outdir, Json::Value& newJsonNode, Json::Value& parentJsonNode,float geometricError, float& geometricErrorOfFirstLevel);
};



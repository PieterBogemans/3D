#include "primitives/mesh-reader.h"
#include "primitives/triangle-primitive.h"
#include "primitives/union-primitive.h"
#include <fstream>
#include <sstream>
#include "logging.h"
#include "easylogging++.h"	

using namespace raytracer;
using namespace raytracer::primitives;
using namespace std;
using namespace math;

std::vector<Primitive> read_mesh(const std::string& path)
{
	std::ifstream ifstream;
	ifstream.open(path, ios::in);

	if (!ifstream.is_open())
	{
		return std::vector<Primitive>();
	}

	std::vector<Point3D> points;
	std::vector<Primitive> triangles;
	std::string line;
	std::getline(ifstream, line); 
	std::string element; 
	std::istringstream iss1(line);
	iss1 >> element;
	int totalPoints = 0;
	int totalTriangles = 0;
	triangles.reserve(80000);
	
	
	while (element != "element") 
	{
		std::getline(ifstream, line);
		std::istringstream iss2(line);
		iss2 >> element;
		LOG(INFO) << line;
		
	}
	std::istringstream iss3(line);
	iss3 >> element;
	iss3 >> element;
	iss3 >> totalPoints;
	LOG(INFO) << totalPoints;

	while (element != "element") 
	{
		std::getline(ifstream, line);
		std::istringstream iss4(line);
		iss4 >> element;
		LOG(INFO) << line;
	}

	std::istringstream iss5(line);
	iss5 >> element;
	iss5 >> element;
	iss5 >> totalTriangles;
	LOG(INFO) << totalTriangles;


	while (line != "end_header") 
	{
		std::getline(ifstream, line);
		LOG(INFO) << line;
	}


	for (int i = 0; i < totalPoints; i++)
	{

		std::getline(ifstream, line);
		
		std::istringstream pointstream(line);
		double x, y, z;
		pointstream >> x >> y >> z;

		Point3D point(x, y, z);
		points.push_back(point);
		/*
		*/

	}
	LOG(INFO) << points.size();
	LOG(INFO) << totalTriangles;
	LOG(INFO) << triangles.max_size();

	for (int i = 0; i < 20000; i++)
	{
		std::getline(ifstream, line);
		std::istringstream trianglestream(line);
		int total, p1, p2, p3;
		
		trianglestream >> total >> p1 >> p2 >> p3;
		

		

		triangles.push_back(triangle(points[p1], points[p2], points[p3]));
	}
	LOG(INFO) << triangles[0];
	LOG(INFO) << triangles.size();


	return triangles;
}

#include "primitives/bounding-box-accelerator.h"
Primitive raytracer::primitives::mesh_obj(const std::string& path)
{

	Primitive mesh = make_union(read_mesh(path));
	

	return mesh;
}
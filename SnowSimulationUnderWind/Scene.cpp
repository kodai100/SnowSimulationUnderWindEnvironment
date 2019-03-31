#include "Scene.h"

Scene::Scene() {}
Scene::Scene(const Scene& scene) {}
Scene::~Scene() {}

Scene* Scene::snowman() {
	Scene* scene = new Scene();

	Shape* snowball = Shape::generateSnowball(Vector2f(1, .16), .15, Vector2f(0, 0));
	scene->snow_shapes.push_back(snowball);

	Shape* snowball2 = Shape::generateSnowball(Vector2f(1, .4), .1, Vector2f(0, 0));
	scene->snow_shapes.push_back(snowball2);

	Shape* snowball3 = Shape::generateSnowball(Vector2f(1, .57), .07, Vector2f(0, 0));
	scene->snow_shapes.push_back(snowball3);

	return scene;
}

Scene* Scene::olaf() {
	Scene* scene = new Scene();

	Shape* foot1 = new Shape(Vector2f(0, 0));
	foot1->addPoint(0.88, 0.07);
	foot1->addPoint(0.97, 0.07);
	foot1->addPoint(0.97, 0.005);
	foot1->addPoint(0.88, 0.005);
	scene->snow_shapes.push_back(foot1);

	Shape* foot2 = new Shape(Vector2f(0, 0));
	foot2->addPoint(1.03, 0.005);
	foot2->addPoint(1.12, 0.005);
	foot2->addPoint(1.12, 0.07);
	foot2->addPoint(1.03, 0.07);
	scene->snow_shapes.push_back(foot2);

	Shape* hip = new Shape(Vector2f(0, 0));
	hip->addPoint(0.86, 0.07);
	hip->addPoint(1.14, 0.07);
	hip->addPoint(1.14, 0.32);
	hip->addPoint(0.86, 0.32);
	scene->snow_shapes.push_back(hip);

	Shape* body = new Shape(Vector2f(0, 0));
	body->addPoint(0.89, 0.32);
	body->addPoint(1.11, 0.32);
	body->addPoint(1.11, 0.49);
	body->addPoint(0.89, 0.49);
	scene->snow_shapes.push_back(body);

	Shape* head = new Shape(Vector2f(0, 0));
	head->addPoint(0.93, 0.49);
	head->addPoint(1.07, 0.49);
	head->addPoint(1.16, 0.71);
	head->addPoint(1.15, 0.77);
	head->addPoint(1.12, 0.78);
	head->addPoint(1.1, 0.95);
	head->addPoint(0.9, 0.95);
	head->addPoint(0.88, 0.78);
	head->addPoint(0.85, 0.77);
	head->addPoint(0.84, 0.71);
	scene->snow_shapes.push_back(head);

	//Shape* snowball4 = Shape::generateSnowball(Vector2f(1.8, .4), .08, Vector2f(-20, -5));
	//scene->snow_shapes.push_back(snowball4);


	return scene;
}

Scene* Scene::snowmanSmash() {
	Scene* scene = new Scene();

	Shape* snowball = Shape::generateSnowball(Vector2f(1, .16), .15, Vector2f(0, 0));
	scene->snow_shapes.push_back(snowball);

	Shape* snowball2 = Shape::generateSnowball(Vector2f(1, .4), .1, Vector2f(0, 0));
	scene->snow_shapes.push_back(snowball2);

	Shape* snowball3 = Shape::generateSnowball(Vector2f(1, .57), .07, Vector2f(0, 0));
	scene->snow_shapes.push_back(snowball3);

	Shape* snowball4 = Shape::generateSnowball(Vector2f(1.8, .4), .08, Vector2f(-20, -5));
	scene->snow_shapes.push_back(snowball4);

	return scene;
}

Scene* Scene::snowballSmash() {

	Scene* scene = new Scene();

	Shape* snowball = Shape::generateSnowball(Vector2f(1.6, .65), .15, Vector2f(-10, 0));
	scene->snow_shapes.push_back(snowball);

	Shape* snowball2 = Shape::generateSnowball(Vector2f(.3, .4), .15, Vector2f(10, 0));
	scene->snow_shapes.push_back(snowball2);

	return scene;
}

Scene* Scene::highspeedSnowballSmash() {
	Scene* scene = new Scene();

	Shape* snowball = Shape::generateSnowball(Vector2f(1.6, .6), .15, Vector2f(-20, 0));
	scene->snow_shapes.push_back(snowball);

	Shape* snowball2 = Shape::generateSnowball(Vector2f(.3, .4), .15, Vector2f(20, 0));
	scene->snow_shapes.push_back(snowball2);

	return scene;
}
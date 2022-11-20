#include "Object/Light/PointLight.hpp"
#include "Scene.hpp"

namespace isim
{
Scene::Scene(const nlohmann::json& json)
{
	addLights(json["lights"]);
	addCameras(json["cameras"]);
	addObjects(json["objects"]);
}

Scene::Scene()
{
}

void Scene::addCameras(const nlohmann::json& cameras)
{
	for (const auto& camera : cameras)
	{
		auto obj = TheFactories["camera"]->New(camera);
		if (dynamic_cast<Camera*>(obj) != nullptr)
		{
			m_cameras.emplace(static_cast<Camera*>(obj));
		}
		else if (obj != nullptr)
		{
			delete obj;
		}
	}
}

void Scene::addLights(const nlohmann::json& lights)
{
	for (const auto& light : lights)
	{
		auto obj = TheFactories[light["type"]]->New(light);
		if (dynamic_cast<Light*>(obj) != nullptr)
		{
			m_lights.emplace(static_cast<Light*>(obj));
		}
		else if (obj != nullptr)
		{
			delete obj;
		}
	}
}

void Scene::addObjects(const nlohmann::json& objects)
{
	for (const auto& object : objects)
	{
		auto obj = TheFactories[object["type"]]->New(object);
		if (dynamic_cast<MeshObject*>(obj) != nullptr)
		{
			m_objects.emplace(static_cast<MeshObject*>(obj));
		}
		else if (obj != nullptr)
		{
			delete obj;
		}
	}
}

const std::set<std::unique_ptr<Camera>>& Scene::getCameras() const
{
	return m_cameras;
}

const std::set<std::unique_ptr<Light>>& Scene::getLights() const
{
	return m_lights;
}

const std::set<std::unique_ptr<MeshObject>>& Scene::getObjects() const
{
	return m_objects;
}

Color Scene::castRay(Ray& ray, int depth) const
{
	static Color COLOR_BLACK = Color(0, 0, 0, 255);

	if (depth == 0)
	{
		return COLOR_BLACK;
	}

	this->castRayObjects(ray);
	if (ray.didHit())
	{
		return this->castRayLights(ray);
	}
	return COLOR_BLACK;
}

void Scene::castRayObjects(Ray& ray) const
{
	for (auto it = m_objects.begin(); it != m_objects.end(); it++)
	{
		Ray newRay = ray;
		if ((*it)->isIntersected(newRay))
		{
			if (newRay.distance < ray.distance)
			{
				ray = newRay;
				ray.obj = (*it).get();
			}
		}
	}
}

Color Scene::castRayLights(Ray& ray) const
{
	// TO-DO: finish
	const auto info = static_cast<const MeshObject*>(ray.obj)->getMaterial(ray)->getInfo(ray);
	Color color = info.color;
	auto kd = info.kd;

	/*float delta = 0.0;
	for (auto it = this->LightsBegin(); it != this->LightsEnd(); it++)
	{
		auto light = (*it).get();
		Ray lightRay;
		lightRay.startpos = ray.endpos;
		lightRay.dir = light->GetCenter() - lightRay.startpos;
		lightRay.dir.Normalize();
		this->CastRayObjects(lightRay);

		if (!lightRay.DidHit())
		{
			Vector normal = ray.obj->GetNormal(ray.endpos);
			Vector L = light->GetCenter() - ray.endpos;
			L.Normalize();

			delta += std::max(0.0f, light->GetIntensity() * normal.DotProduct(L) * kd);
		}
	}
	return Color(std::clamp<std::int16_t>(color.r * delta, 0, 255),
				 std::clamp<std::int16_t>(color.g * delta, 0, 255),
				 std::clamp<std::int16_t>(color.b * delta, 0, 255));*/

	return color;
}
};
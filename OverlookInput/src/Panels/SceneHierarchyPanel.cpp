#include "SceneHierarchyPanel.h"

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

#include <glm/gtc/type_ptr.hpp>

#include "magic_enum.hpp"

#include "Overlook/Scene/Components.h"
#include "Overlook/Utils/PlatformUtils.h"
#include "Overlook/Scripting/ScriptEngine.h"

#include "Overlook/ImGui/ImGuiWrapper.h"

#include <cstring>
#include <regex>

/* The Microsoft C++ compiler is non-compliant with the C++ standard and needs
 * the following definition to disable a security warning on std::strncpy().
 */
#ifdef _MSVC_LANG
#define _CRT_SECURE_NO_WARNINGS
#endif


namespace Overlook {
	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& context)
	{
		SetContext(context);
	}

	void SceneHierarchyPanel::SetContext(const Ref<Scene>& context)
	{
		mContext = context;
		mSelectionContext = {};
	}

	void SceneHierarchyPanel::OnImGuiRender(bool* pOpen, bool* pOpenProperties)
	{
		if (*pOpen)
		{
			ImGui::Begin("Scene Hierarchy", pOpen);

			if (mContext)
			{
				mContext->m_Registry.each([&](auto entityID)
					{
						Entity entity = { entityID, mContext.get() };
						DrawEntityNode(entity);
					});

				if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
					mSelectionContext = {};

				// Right-click on blank space
				if (ImGui::BeginPopupContextWindow(0, 1, false))
				{
					if (ImGui::MenuItem("Create Empty Entity"))
						mContext->CreateEntity("Empty Entity");

					if (ImGui::MenuItem("Create Directional Light"))
					{
						auto entity = mContext->CreateEntity("Directional Light");
						entity.AddComponent<DirectionalLightComponent>();
						SetSelectedEntity(entity);
					}

					ImGui::EndPopup();
				}
			}

			ImGui::End();
		}
		if (*pOpenProperties)
		{
			ImGui::Begin("Properties", pOpenProperties);
			if (mSelectionContext)
			{
				DrawComponents(mSelectionContext);
			}
			ImGui::End();
		}
	}

	void SceneHierarchyPanel::SetSelectedEntity(Entity entity)
	{
		mSelectionContext = entity;
	}

	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		const char* name = "Unnamed Entity";
		if (entity.HasComponent<TagComponent>())
		{
			name = entity.GetComponent<TagComponent>().Tag.c_str();
		}

		ImGuiTreeNodeFlags flags = ((mSelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		flags |= ImGuiTreeNodeFlags_SpanAvailWidth;

		std::string label = std::string("##") + std::string(name);
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, "");
		if (ImGui::IsItemClicked())
		{
			mSelectionContext = entity;
		}
		bool entityDeleted = false;
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete Entity"))
				entityDeleted = true;

			ImGui::EndPopup();
		}
		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(1.0f, 1.0f, 1.0f, 0.0f));
		ImGui::Image((ImTextureID)IconManager::GetInstance().Get("EntityIcon")->GetRendererID(), ImVec2{ lineHeight - 5.0f, lineHeight - 5.0f }, { 0, 1 }, { 1, 0 });
		ImGui::PopStyleColor(1);
		ImGui::SameLine();
		ImGui::Text(name);

		if (opened)
		{
			ImGui::TreePop();
		}

		if (entityDeleted)
		{
			mContext->DestroyEntity(entity);
			if (mSelectionContext == entity)
				mSelectionContext = {};
		}
	}

	static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f)
	{
		ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];

		ImGui::Columns(2, nullptr, false);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::BeginTable("table_padding", 3, ImGuiTableFlags_NoBordersInBody | ImGuiTableFlags_NoPadInnerX);

		ImGui::TableNextRow();
		ImGui::TableSetColumnIndex(0);

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("X", buttonSize))
			values.x = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::SameLine();


		ImGui::TableSetColumnIndex(1);

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Y", buttonSize))
			values.y = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::SameLine();

		ImGui::TableSetColumnIndex(2);

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Z", buttonSize))
			values.z = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");

		ImGui::PopStyleVar();

		ImGui::EndTable();

		ImGui::EndColumns();
	}

	template <typename T, typename UIFunction>
	static void DrawComponent(const std::string& name, Entity entity, UIFunction uiFunction)
	{
		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;

		if (entity.HasComponent<T>())
		{
			auto& component = entity.GetComponent<T>();
			ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();

			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			bool open = ImGuiWrapper::TreeNodeExStyle1((void*)typeid(T).hash_code(), name, treeNodeFlags);
			ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);

			if (ImGui::ImageButton((ImTextureID)IconManager::GetInstance().GetSettingIcon()->GetRendererID(), ImVec2{ lineHeight - 7.0f, lineHeight - 7.0f }))
			{
				ImGui::OpenPopup("ComponentSettings");
			}

			bool removeComponent = false;
			if (ImGui::BeginPopup("ComponentSettings"))
			{
				if (ImGui::MenuItem("Remove component"))
					removeComponent = true;

				ImGui::EndPopup();
			}

			if (open)
			{
				uiFunction(component);
				ImGui::TreePop();
			}

			if (removeComponent)
				entity.RemoveComponent<T>();
		}
	}

	template <typename componentType>
	void SceneHierarchyPanel::MenuAddComponent(const char* menuName, const char* menuItemName)
	{
		if (!mSelectionContext.HasComponent<componentType>())
		{
			if (ImGui::BeginMenu(menuName))
			{
				if (ImGui::MenuItem(menuItemName))
				{
					mSelectionContext.AddComponent<componentType>();
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndMenu();
			}
		}
	}

	void SceneHierarchyPanel::DrawComponents(Entity entity)
	{
		if (entity.HasComponent<TagComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>().Tag;

			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), tag.c_str());
			if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
			{
				tag = std::string(buffer);
			}
		}

		ImGui::SameLine();
		ImGui::PushItemWidth(-1);

		if (ImGui::Button("Add Component"))
			ImGui::OpenPopup("AddComponent");

		if (ImGui::BeginPopup("AddComponent"))
		{
			MenuAddComponent<CameraComponent>("Camera", "Camera");
			MenuAddComponent<ScriptComponent>("Script", "Script");

			if (ModeManager::b3DMode)
			{
				MenuAddComponent<ModelRendererComponent>("Mesh", "Mesh Renderer");

				if (mSelectionContext.HasComponent<ModelRendererComponent>())
					MenuAddComponent<Rigidbody3DComponent>("Physic", "Rigidbody");


				MenuAddComponent<DirectionalLightComponent>("Light", "Directional Light");
			}
			else
			{
				MenuAddComponent<SpriteRendererComponent>("Renderer", "Sprite Renderer");
			}

			ImGui::EndPopup();
		}

		ImGui::PopItemWidth();

		DrawComponent<TransformComponent>("Transform", entity, [](auto& component)
			{
				DrawVec3Control("Translation", component.Translation);
				glm::vec3 rotation = glm::degrees(component.Rotation);
				DrawVec3Control("Rotation", rotation);
				component.Rotation = glm::radians(rotation);
				DrawVec3Control("Scale", component.Scale, 1.0f);
			});

		DrawComponent<CameraComponent>("Camera", entity, [](auto& component)
			{
				auto& camera = component.Camera;

				ImGui::Checkbox("Primary", &component.Primary);

				const char* projectionTypeStrings[] = { "Perspective", "Orthographic" };
				const char* currentProjectionTypeString = projectionTypeStrings[(int)camera.GetProjectionType()];
				if (ImGui::BeginCombo("Projection", currentProjectionTypeString))
				{
					for (int i = 0; i < 2; i++)
					{
						bool isSelected = (currentProjectionTypeString == projectionTypeStrings[i]);
						if (ImGui::Selectable(projectionTypeStrings[i], isSelected))
						{
							currentProjectionTypeString = projectionTypeStrings[i];
							camera.SetProjectionType((SceneCamera::ProjectionType)i);
						}

						if (isSelected)
							ImGui::SetItemDefaultFocus();
					}

					ImGui::EndCombo();
				}

				if (camera.GetProjectionType() == SceneCamera::ProjectionType::Perspective)
				{
					float perspectiveVerticalFov = glm::degrees(camera.GetPerspectiveVerticalFOV());
					if (ImGui::DragFloat("Vertical FOV", &perspectiveVerticalFov))
						camera.SetPerspectiveVerticalFOV(glm::radians(perspectiveVerticalFov));

					float perspectiveNear = camera.GetPerspectiveNearClip();
					if (ImGui::DragFloat("Near", &perspectiveNear))
						camera.SetPerspectiveNearClip(perspectiveNear);

					float perspectiveFar = camera.GetPerspectiveFarClip();
					if (ImGui::DragFloat("Far", &perspectiveFar))
						camera.SetPerspectiveFarClip(perspectiveFar);
				}

				if (camera.GetProjectionType() == SceneCamera::ProjectionType::Orthographic)
				{
					float orthoSize = camera.GetOrthographicSize();
					if (ImGui::DragFloat("Size", &orthoSize))
						camera.SetOrthographicSize(orthoSize);

					float orthoNear = camera.GetOrthographicNearClip();
					if (ImGui::DragFloat("Near", &orthoNear))
						camera.SetOrthographicNearClip(orthoNear);

					float orthoFar = camera.GetOrthographicFarClip();
					if (ImGui::DragFloat("Far", &orthoFar))
						camera.SetOrthographicFarClip(orthoFar);

					ImGui::Checkbox("Fixed Aspect Ratio", &component.FixedAspectRatio);
				}
			});

		DrawComponent<ScriptComponent>("Script", entity, [entity, scene = mContext](auto& component) mutable
			{
				bool scriptClassExists = ScriptEngine::EntityClassExists(component.ClassName);

				static char buffer[64];
				strcpy_s(buffer, sizeof(buffer), component.ClassName.c_str());

				if (!scriptClassExists)
					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.9f, 0.2f, 0.3f, 1.0f));

				if (ImGui::InputText("Class", buffer, sizeof(buffer)))
					component.ClassName = buffer;

				// Fields
				bool sceneRunning = scene->IsRunning();
				if (sceneRunning)
				{
					Ref<ScriptInstance> scriptInstance = ScriptEngine::GetEntityScriptInstance(entity.GetUUID());
					if (scriptInstance)
					{
						const auto& fields = scriptInstance->GetScriptClass()->GetFields();
						for (const auto& [name, field] : fields)
						{
							if (field.Type == ScriptFieldType::Float)
							{
								float data = scriptInstance->GetFieldValue<float>(name);
								if (ImGui::DragFloat(name.c_str(), &data))
								{
									scriptInstance->SetFieldValue(name, data);
								}
							}
						}
					}
				}
				else
				{
					if (scriptClassExists)
					{
						Ref<ScriptClass> entityClass = ScriptEngine::GetEntityClass(component.ClassName);
						const auto& fields = entityClass->GetFields();

						auto& entityFields = ScriptEngine::GetScriptFieldMap(entity);
						for (const auto& [name, field] : fields)
						{
							// Field has been set in editor
							if (entityFields.find(name) != entityFields.end())
							{
								ScriptFieldInstance& scriptField = entityFields.at(name);

								// Display control to set it maybe
								if (field.Type == ScriptFieldType::Float)
								{
									float data = scriptField.GetValue<float>();
									if (ImGui::DragFloat(name.c_str(), &data))
										scriptField.SetValue(data);
								}
							}
							else
							{
								// Display control to set it maybe
								if (field.Type == ScriptFieldType::Float)
								{
									float data = 0.0f;
									if (ImGui::DragFloat(name.c_str(), &data))
									{
										ScriptFieldInstance& fieldInstance = entityFields[name];
										fieldInstance.Field = field;
										fieldInstance.SetValue(data);
									}
								}
							}
						}
					}
				}

				if (!scriptClassExists)
					ImGui::PopStyleColor();
			});

		DrawComponent<SpriteRendererComponent>("Sprite Render", entity, [](auto& component)
			{
				ImGui::ColorEdit4("Color", glm::value_ptr(component.Color));

				ImGui::Button("Texture", ImVec2(100.0f, 0.0f));
				if (ImGui::BeginDragDropTarget())
				{
					if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
					{
						const wchar_t* path = (const wchar_t*)payload->Data;
						std::filesystem::path texturePath = std::filesystem::path(ConfigManager::GetInstance().GetAssetsFolder()) / path;
						Ref<Texture2D> texture = Texture2D::Create(texturePath.string());
						if (texture->IsLoaded())
							component.Texture = texture;
						else
							OL_WARN("Could not load texture {0}", texturePath.filename().string());
					}
					ImGui::EndDragDropTarget();
				}

				ImGui::DragFloat("Tiling Factor", &component.TilingFactor, 0.1f, 0.0f, 100.0f);
			});

		DrawComponent<ModelRendererComponent>("Mesh Renderer", entity, [](ModelRendererComponent& component)
			{
				ImGui::Columns(2, nullptr, false);
				ImGui::SetColumnWidth(0, 100.0f);
				ImGui::Text("Mesh Path");
				ImGui::NextColumn();

				std::string standardPath = std::regex_replace(component.Path, std::regex("\\\\"), "/");
				ImGui::Text(std::string_view(standardPath.c_str() + standardPath.find_last_of("/") + 1, standardPath.length()).data());
				if (ImGui::BeginDragDropTarget())
				{
					if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
					{
						auto path = (const wchar_t*)payload->Data;
						component.Path = (std::filesystem::path("assets") / path).string();
						component.mMesh = CreateRef<Mesh>(component.Path);
					}
					ImGui::EndDragDropTarget();
				}

				ImGui::SameLine();
				if (ImGui::Button("..."))
				{
					std::string filepath = FileDialogs::OpenFile("Model (*.obj *.fbx *.dae *.gltf)\0");
					if (filepath.find("assets") != std::string::npos)
					{
						filepath = filepath.substr(filepath.find("assets"), filepath.length());
					}
					else
					{
						// TODO: Import Mesh
						//OL_CORE_ASSERT(false, "HEngine Now Only support the model from assets!");
						//filepath = "";
					}
					if (!filepath.empty())
					{
						component.mMesh = CreateRef<Mesh>(filepath);
						component.Path = filepath;
					}
				}
				ImGui::EndColumns();

				if (ImGuiWrapper::TreeNodeExStyle2((void*)"Material", "Material"))
				{
					uint32_t matIndex = 0;

					const auto& materialNode = [&matIndex = matIndex](const char* name, Ref<Material>& material, Ref<Texture2D>& tex, void(*func)(Ref<Material>& mat)) {
						std::string label = std::string(name) + std::to_string(matIndex);
						ImGui::PushID(label.c_str());

						if (ImGui::TreeNode((void*)name, name))
						{
							ImGui::Image((ImTextureID)tex->GetRendererID(), ImVec2(64, 64), ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
							if (ImGui::BeginDragDropTarget())
							{
								if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
								{
									auto path = (const wchar_t*)payload->Data;
									std::string relativePath = (std::filesystem::path("assets") / path).string();
									std::filesystem::path texturePath = ConfigManager::GetInstance().GetAssetsFolder() / path;
									relativePath = std::regex_replace(relativePath, std::regex("\\\\"), "/");
									tex = IconManager::GetInstance().LoadOrFindTexture(relativePath);
								}
								ImGui::EndDragDropTarget();
							}

							func(material);

							ImGui::TreePop();
						}

						ImGui::PopID();
					};

					for (auto& material : component.mMesh->mMaterial)
					{
						std::string label = std::string("material") + std::to_string(matIndex);
						ImGui::PushID(label.c_str());

						if (ImGui::TreeNode((void*)label.c_str(), std::to_string(matIndex).c_str()))
						{
							materialNode("Albedo", material, material->mAlbedoMap, [](Ref<Material>& mat) {
								ImGui::SameLine();
								ImGui::Checkbox("Use", &mat->bUseAlbedoMap);

								if (ImGui::ColorEdit4("##albedo", glm::value_ptr(mat->col)))
								{
									if (!mat->bUseAlbedoMap)
									{
										unsigned char data[4];
										for (size_t i = 0; i < 4; i++)
										{
											data[i] = (unsigned char)(mat->col[i] * 255.0f);
										}
										mat->albedoRGBA->SetData(data, sizeof(unsigned char) * 4);
									}
								}
								});

							materialNode("Normal", material, material->mNormalMap, [](Ref<Material>& mat) {
								ImGui::SameLine();
								ImGui::Checkbox("Use", &mat->bUseNormalMap);
								});

							materialNode("Metallic", material, material->mMetallicMap, [](Ref<Material>& mat) {
								ImGui::SameLine();

								if (ImGui::BeginTable("Metallic", 1))
								{
									ImGui::TableNextRow();
									ImGui::TableNextColumn();

									ImGui::Checkbox("Use", &mat->bUseMetallicMap);

									ImGui::TableNextRow();
									ImGui::TableNextColumn();
									if (ImGui::SliderFloat("##Metallic", &mat->metallic, 0.0f, 1.0f))
									{
										if (!mat->bUseMetallicMap)
										{
											unsigned char data[4];
											for (size_t i = 0; i < 3; i++)
											{
												data[i] = (unsigned char)(mat->metallic * 255.0f);
											}
											data[3] = (unsigned char)255.0f;
											mat->metallicRGBA->SetData(data, sizeof(unsigned char) * 4);
										}
									}

									ImGui::EndTable();
								}
								});

							materialNode("Roughness", material, material->mRoughnessMap, [](Ref<Material>& mat) {
								ImGui::SameLine();

								if (ImGui::BeginTable("Roughness", 1))
								{
									ImGui::TableNextRow();
									ImGui::TableNextColumn();

									ImGui::Checkbox("Use", &mat->bUseRoughnessMap);

									ImGui::TableNextRow();
									ImGui::TableNextColumn();
									if (ImGui::SliderFloat("##Roughness", &mat->roughness, 0.0f, 1.0f))
									{
										if (!mat->bUseRoughnessMap)
										{
											unsigned char data[4];
											for (size_t i = 0; i < 3; i++)
											{
												data[i] = (unsigned char)(mat->roughness * 255.0f);
											}
											data[3] = (unsigned char)255.0f;
											mat->roughnessRGBA->SetData(data, sizeof(unsigned char) * 4);
										}
									}

									ImGui::EndTable();
								}
								});

							ImGui::TreePop();
						}

						matIndex++;

						ImGui::PopID();
					}

					ImGui::TreePop();
				}
				});

		DrawComponent<Rigidbody3DComponent>("Rigidbody 3D", entity, [](auto& component)
			{
				const char* bodyTypeStrings[] = { "Static", "Dynamic", "Kinematic" };
				const char* currentBodyTypeString = bodyTypeStrings[(int)component.Type];

				ImGui::Columns(2, nullptr, false);
				ImGui::SetColumnWidth(0, 150.0f);
				ImGui::Text("Body Type");
				ImGui::NextColumn();
				if (ImGui::BeginCombo("##Body Type", currentBodyTypeString))
				{
					for (int i = 0; i < 3; i++)
					{
						bool isSelected = currentBodyTypeString == bodyTypeStrings[i];
						if (ImGui::Selectable(bodyTypeStrings[i], isSelected))
						{
							currentBodyTypeString = bodyTypeStrings[i];
							component.Type = (Rigidbody3DComponent::Body3DType)i;
						}

						if (isSelected)
							ImGui::SetItemDefaultFocus();
					}

					ImGui::EndCombo();
				}
				ImGui::EndColumns();

				ImGui::Columns(2, nullptr, false);
				ImGui::SetColumnWidth(0, 150.0f);
				ImGui::Text("Collision Shape");
				ImGui::NextColumn();
				constexpr auto collisionShapes = magic_enum::enum_values<CollisionShape>();
				if (ImGui::BeginCombo("##Collision Shape", magic_enum::enum_name(component.Shape).data()))
				{
					for (auto& shape : collisionShapes)
					{
						bool isSelected = component.Shape == shape;
						if (ImGui::Selectable(magic_enum::enum_name(shape).data(), isSelected))
						{
							component.Shape = shape;
						}

						if (isSelected)
							ImGui::SetItemDefaultFocus();
					}

					ImGui::EndCombo();
				}
				ImGui::EndColumns();

				if (component.Shape != CollisionShape::None)
				{
					const auto& floatValueUI = [](const char* name, float& value) {
						ImGui::Columns(2, nullptr, false);
						ImGui::SetColumnWidth(0, 150.0f);
						ImGui::Text(name);
						ImGui::NextColumn();
						std::string label = std::string("##") + std::string(name);
						ImGui::SliderFloat(label.c_str(), &value, 0.0f, 1.0f, "%.2f");
						ImGui::EndColumns();
					};

					floatValueUI("linearDamping", component.linearDamping);
					floatValueUI("angularDamping", component.angularDamping);
					floatValueUI("restitution", component.restitution);
					floatValueUI("friction", component.friction);
				}

				ImGuiWrapper::DrawTwoUI(
					[]() { ImGui::Text("mass"); },
					[&component = component]() { ImGui::SliderFloat("##masas", &component.mass, 0.0f, 10.0f, "%.2f"); },
					150.0f
				);
			});

		DrawComponent<DirectionalLightComponent>("Directional Light", entity, [](auto& component)
			{
				ImGuiWrapper::DrawTwoUI(
					[]() { ImGui::Text("Light Intensity"); },
					[&component = component]() { ImGui::SliderFloat("##Light Intensity", &component.Intensity, 0.0f, 10.0f, "%.2f"); }
				);
			});

	}
}
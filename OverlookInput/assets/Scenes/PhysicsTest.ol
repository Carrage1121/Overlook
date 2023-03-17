Scene: Untitled
Entities:
  - Entity: 17507920051290401431
    TagComponent:
      Tag: Empty Entity
    TransformComponent:
      Translation: [13.0336285, 5.07548293e-06, -9.71115685]
      Rotation: [-3.14159226, 0, -3.14159226]
      Scale: [0.5, 0.5, 0.5]
    ScriptComponent:
      ClassName: Sandbox.Player
      ScriptFields:
        - Name: Speed
          Type: Float
          Data: 9
    ModelRendererComponent:
      Path: assets\Model\nanosuit\nanosuit.obj
    Rigidbody3DComponent:
      mass: 1
      type: 0
      shape: 1
      linearDamping: 0
      angularDamping: 0
      restitution: 1
      friction: 1
  - Entity: 5718081194731635970
    TagComponent:
      Tag: floor
    TransformComponent:
      Translation: [0, -5, 0]
      Rotation: [0.0352039076, 0.0492473282, 0.254624188]
      Scale: [20.0000076, 1, 20.0000038]
    ModelRendererComponent:
      Path: assets\Model\Base\Box.obj
    Rigidbody3DComponent:
      mass: 1
      type: 2
      shape: 1
      linearDamping: 0
      angularDamping: 0
      restitution: 1
      friction: 1
  - Entity: 5671806262007915135
    TagComponent:
      Tag: Directional Light
    TransformComponent:
      Translation: [4.32344279e-07, 5.97650528, 5.59594298e-07]
      Rotation: [-2.12406564, -0.0188495573, -2.98276758]
      Scale: [0.999999046, 1, 0.999999046]
    DirectionalLightComponent:
      dirIntensity: 2.93000007
  - Entity: 13251675636020269026
    TagComponent:
      Tag: Camera
    TransformComponent:
      Translation: [7.69081112e-07, 2, -15]
      Rotation: [-3.14159226, 0, -3.14159226]
      Scale: [1, 1, 1]
    CameraComponent:
      Camera:
        ProjectionType: 1
        PerspectiveFOV: 0.785398185
        PerspectiveNear: 0.00999999978
        PerspectiveFar: 1000
        OrthographicSize: 10
        OrthographicNear: -1
        OrthographicFar: 1
      Primary: true
      FixedAspectRatio: false
    ScriptComponent:
      ClassName: Sandbox.Camera
      ScriptFields:
        []
  - Entity: 10399201563783663200
    TagComponent:
      Tag: Boll
    TransformComponent:
      Translation: [2.98023224e-08, 5, 0]
      Rotation: [0, 0, 0]
      Scale: [1, 1, 1]
    ModelRendererComponent:
      Path: assets\Model\Base\Sphere.obj
    Rigidbody3DComponent:
      mass: 1
      type: 1
      shape: 2
      linearDamping: 0
      angularDamping: 0
      restitution: 1
      friction: 1
  - Entity: 6274030695351376918
    TagComponent:
      Tag: squre
    TransformComponent:
      Translation: [1.578704, 1.10742199, -1.5890497]
      Rotation: [0, 0, 0]
      Scale: [0.99000001, 0.99000001, 0.99000001]
    ModelRendererComponent:
      Path: assets\Model\Base\Box.obj
    Rigidbody3DComponent:
      mass: 6.4000001
      type: 1
      shape: 1
      linearDamping: 0
      angularDamping: 0
      restitution: 1
      friction: 0.300000012
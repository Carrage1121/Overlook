Scene: Untitled
Entities:
  - Entity: 5064509501229496281
    TagComponent:
      Tag: Camera
    TransformComponent:
      Translation: [0, 0, 0]
      Rotation: [0, 0, 0]
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
  - Entity: 7998278600884310929
    TagComponent:
      Tag: box
    TransformComponent:
      Translation: [0, 0, 0]
      Rotation: [0, 0, 0]
      Scale: [1, 1, 1]
    ScriptComponent:
      ClassName: Sandbox.Player
      ScriptFields:
        []
    ModelRendererComponent:
      Path: assets\Model\Base\Box.obj
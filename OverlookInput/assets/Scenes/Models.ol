Scene: Untitled
Entities:
  - Entity: 10856126255045384523
    TagComponent:
      Tag: Model2
    TransformComponent:
      Translation: [-0.0278813243, 2.32331467, -1.5301019]
      Rotation: [0, 0, 0]
      Scale: [1, 1, 1]
    ModelRendererComponent:
      Path: assets\Model\G18\gun.obj
  - Entity: 12837192831273
    TagComponent:
      Tag: Sprite
    TransformComponent:
      Translation: [0, 0, 0]
      Rotation: [0, 0, 0]
      Scale: [1, 1, 1]
  - Entity: 12837192831273
    TagComponent:
      Tag: Camera
    TransformComponent:
      Translation: [0, 0, 10]
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
  - Entity: 12837192831273
    TagComponent:
      Tag: Model
    TransformComponent:
      Translation: [0, 0, 0]
      Rotation: [0, 0, 0]
      Scale: [0.783199906, 0.783199906, 0.783199906]
    ModelRendererComponent:
      Path: assets\Model\backpack\backpack.obj
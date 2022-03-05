using System;
using System.IO;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;
using UnityEditor.SceneManagement;
using UnityEngine.SceneManagement;

enum QualitySetting { Production, Draft }

// unity only allows menu items to be created for static methods
class StadiaImportScene {
    [MenuItem("Stadia/Import Scene")]
    static public void Run() {
        Stadia stadia = new Stadia();
        stadia.ImportScene();
    }
}


public class Stadia {
    // expected fila paths
    private const string aliFilePath = "c:\\eb\\renderer_input\\model.ali";
    private const string doorsFilePath = "c:\\eb\\renderer_input\\model.doors";
    private const string camerasFilePath = "c:\\eb\\renderer_input\\model.cameras";
    private const string infoFilePath = "c:\\eb\\renderer_input\\model.info";
    Log log;
    public Stadia() {
        log = new Log();
    }

    [MenuItem("Stadia/Import Scene")]
    public void ImportScene() {
        
        log.Open("c:\\eb\\scratch\\renderer.log");
        log.Write("unity ImportScene started");

        // track model size
        int triCount = 0;
        int lightCount = 0;
        List<string> doors;
        EditorSceneManager.OpenScene("Assets/scene.unity");
        // general scene setup
        PlaceSun();
        SetPlayerSettings();

        // get list of doors
        log.Write("getting Doors");
        if (!File.Exists(doorsFilePath))
            throw new System.IO.FileNotFoundException("Ali file not found at " + doorsFilePath);
        doors = new List<string>(File.ReadAllLines(doorsFilePath));

        // create ali reader
        log.Write("creating reader");
        if (!File.Exists(aliFilePath))
            throw new System.IO.FileNotFoundException("Ali file not found at " + aliFilePath);
        Reader r = new Reader(aliFilePath);

        // generate materials
        log.Write("generating materials");
        while (r.NextElementIsMaterial()) {
            MaterialData mat;
            mat = r.NextMaterial();
            BuildMaterial(mat);
        }

        // generate lights
        log.Write("placing lights");
        while (r.NextElementIsLight()) {
            LightData light;
            light = r.NextLight();
            BuildLight(light);
            lightCount++;
        }
        log.Write("created " + lightCount + " lights");

        // place first person controller
        log.Write("creating first person controller");
        BuildFirstPersonController();

        // generate geometry
        log.Write("creating building meshes");
        while (r.NextElementIsMesh()) {
            MeshData m;
            m = r.NextMesh();
            log.Write("creating mesh" + m.name);
            triCount += BuildMesh(m, doors);
        }
        log.Write("triangle count is " + triCount);


        const string scenePath = "Assets/scene.unity";
        log.Write("saving scene at " + scenePath);
        EditorSceneManager.SaveScene(SceneManager.GetActiveScene(), scenePath);
        log.Write("simulating lighting " + scenePath);
        SimulateLighting(triCount, lightCount, QualitySetting.Production);
        string[] levels = new string[1] { scenePath };
        log.Write("building player");
        BuildPipeline.BuildPlayer(levels, "rendering.exe", BuildTarget.StandaloneWindows, BuildOptions.None);

        /*} catch (Exception e) {

                log.WriteError("exception reached top level: "+e.Message);
                log.WriteError("exiting with failure code");
                log.Close();
                UnityEditor.EditorApplication.Exit(1);
            }*/
        log.Write("done, exiting with success code");
        log.Close();
        //UnityEditor.EditorApplication.Exit(0);
    }
    private void SimulateLighting(int triCount, int lightCount, QualitySetting quality) {
        /*try {
            // many lightmapping settings are defined in BeastSettings.xml
            // determine file locations
            string lmSettings = Directory.GetCurrentDirectory() + "\\Assets\\scene\\BeastSettings.xml";
            string lmSettingsDraft = Directory.GetCurrentDirectory() + "\\Assets\\scene\\BeastSettings-Draft.xml";

            // linear lighting space makes banding less obvious at high and low exposure settings
            LightmapSettings.bakedColorSpace = ColorSpace.Linear;
            // big models will fail if resolution is too high (memory limited to 1.5gb)
            // big models will take forever to bake if quality (final gather rays, resolution) is too high

            LightmapEditorSettings.aoAmount = 0.0f;    // geometry-only pass, while the ao in BeastSettings.xml is
                                                       // a FinalGather solution.
            LightmapEditorSettings.aoMaxDistance = 2f; // 2 meter rays are considered unoccluded
            LightmapEditorSettings.aoContrast = 1f;

            // set lightmap resolution based on size of model
            if (quality == QualitySetting.Draft) {
                log.Write("lighting quality set to draft");
                LightmapEditorSettings.resolution = 5;
                File.Delete(lmSettings);
                File.Copy(lmSettingsDraft, lmSettings);
            } else if (triCount < 1000000 & lightCount < 200) {
                log.Write("lighting quality set to high");
                LightmapEditorSettings.resolution = 40;
            } else if (triCount < 5000000 & lightCount < 400) {
                log.Write("lighting quality set to medium");
                LightmapEditorSettings.resolution = 25;
            } else { // really big scene or many lights
                log.Write("lighting quality set to low");
                LightmapEditorSettings.resolution = 15;
            }
            //AssetDatabase.ImportAsset("Assets\\scene\\BeastSettings.xml");
            Lightmapping.Clear();
            Lightmapping.Bake();

            // check that the lightmaps loaded correctly
            while (LightmapSettings.lightmaps.Length == 0) {
                // nope. reduce quality settings and try again
                log.WriteWarning("lightmapping failed");
                // sometimes unity/beast runs out of memory (32 bit application) reducing resolution occasionally resolves that.
                LightmapEditorSettings.resolution = LightmapEditorSettings.resolution / 2f;
                File.Delete(lmSettings);
                File.Copy(lmSettingsDraft, lmSettings);
                log.Write("reducing lightmap settings to resolution:" + LightmapEditorSettings.resolution + " and using draft beast settings");
                if (LightmapEditorSettings.resolution < 5) {
                    log.WriteError("resolution is below 5 now, giving up");
                    throw new Exception("unable to simulate lighting");
                }
                Lightmapping.Bake();
            }
            log.Write("lightmapping successful");
        } catch (Exception e) {
            throw e;
        }*/
    }

    private void BuildFirstPersonController() {
        /*const string firstPersonControllerPath = "Assets/Standard Assets/Character Controllers/First Person Controller.prefab";
        GameObject firstPersonController = (GameObject)AssetDatabase.LoadAssetAtPath(firstPersonControllerPath, typeof(GameObject));
        firstPersonController.active = false; // necessary to workaround disabled image effects.
        if (firstPersonController == null) throw new Exception("unable to find first person controller");
        GameObject instantiatedObject = (GameObject)GameObject.Instantiate(firstPersonController);
        instantiatedObject.tag = "firstPersonController";
        // get PositionController component
        PositionController positionController = instantiatedObject.GetComponent<PositionController>();
        if (positionController == null) { // then add the component
            positionController = instantiatedObject.AddComponent<PositionController>();
        }
        // verify cameras file exists
        if (!File.Exists(camerasFilePath))
            throw new System.IO.FileNotFoundException("Ali file not found at " + camerasFilePath);
        // verify info file exists
        if (!File.Exists(infoFilePath))
            throw new System.IO.FileNotFoundException("Ali file not found at " + infoFilePath);
        // read cameras file
        List<string> camerasData = new List<string>(File.ReadAllLines(camerasFilePath));
        // read info file
        List<string> infoData = new List<string>(File.ReadAllLines(infoFilePath));
        // we want to get the data into this list
        List<CameraLocation> cameraLocations = new List<CameraLocation>();
        // incoming german data uses commas as decimal, replace with period
        for (int i = 0; i < camerasData.Count; i++) {
            camerasData[i] = camerasData[i].Replace(",", ".");
        }
        CameraLocation cameraLocation = new CameraLocation();
        // handle 1.5 camera data
        if (infoData[0] == "1.5" | infoData[0] == "1.6") {
            for (int i = 0; i < camerasData.Count; i += 10) {
                cameraLocation.name = camerasData[i];
                // file contents are in inches and use revit's coordinate system
                double xFeet = 0; double yFeet = 0; double zFeet = 0;
                double.TryParse(camerasData[i + 1], out xFeet);
                double.TryParse(camerasData[i + 2], out yFeet);
                double.TryParse(camerasData[i + 3], out zFeet);
                double forwardX = 1; double forwardY = 0; double forwardZ = 0;
                double upX = 0; double upY; double upZ = 1;
                double.TryParse(camerasData[i + 4], out forwardX);
                double.TryParse(camerasData[i + 5], out forwardY);
                double.TryParse(camerasData[i + 6], out forwardZ);
                double.TryParse(camerasData[i + 7], out upX);
                double.TryParse(camerasData[i + 8], out upY);
                double.TryParse(camerasData[i + 9], out upZ);
                // now we have the raw data from revit

                // convert to unity coordinate system
                // the coordinate system and units of measurement are different:
                // Unity x position = Revit x * -feetToMetersCoeffecient
                // Unity y position = Revit z * feetToMetersCoeffecient
                // Unity z position = Revit y * -feetToMetersCoeffecient
                // .cameras units are ft, unity units are m
                const float FtToMCoefficient = 0.3048f;
                Vector3 pos = new Vector3((float)(xFeet * -FtToMCoefficient),
                                          (float)(zFeet * FtToMCoefficient),
                                          (float)(yFeet * -FtToMCoefficient));
                Vector3 forward = new Vector3((float)-forwardX, (float)forwardZ, (float)-forwardY);
                Vector3 up = new Vector3((float)-upX, (float)upZ, (float)-upY);

                // write to cameraLocation storage
                cameraLocation.position = pos;
                cameraLocation.rotation.SetLookRotation(forward, up);
                //cameraLocation.rot
                cameraLocations.Add(new CameraLocation(cameraLocation));
            }
        } else { // handle pre-1.5 data
            for (int i = 0; i < camerasData.Count; i += 7) {
                cameraLocation.name = camerasData[i];
                // file contents are in inches and use revit's coordinate system
                double xFeet = 0; double yFeet = 0; double zFeet = 0;
                double.TryParse(camerasData[i + 1], out xFeet);
                double.TryParse(camerasData[i + 2], out yFeet);
                double.TryParse(camerasData[i + 3], out zFeet);
                double xRot = 0; double yRot = 0; double zRot = 0;
                double.TryParse(camerasData[i + 4], out xRot);
                double.TryParse(camerasData[i + 5], out yRot);
                double.TryParse(camerasData[i + 6], out zRot);
                // now we have the raw data from revit
                // the coordinate system and units of measurement are different:
                // Unity x position = Revit x * -feetToMetersCoeffecient
                // Unity y position = Revit z * feetToMetersCoeffecient
                // Unity z position = Revit y * -feetToMetersCoeffecient
                // .cameras units are ft, unity units are m
                const float FtToMCoefficient = 0.3048f;
                Vector3 pos = new Vector3((float)(xFeet * -FtToMCoefficient),
                                          (float)(zFeet * FtToMCoefficient),
                                          (float)(yFeet * -FtToMCoefficient));
                cameraLocation.position = pos;
                Vector3 rot = new Vector3((float)xRot, (float)yRot, (float)zRot);
                Vector3 viewDir = rot - pos;
                cameraLocation.rotation.eulerAngles = viewDir;
                cameraLocations.Add(cameraLocation);
            }
        }
        CameraLocationHolder cameraLocationHolder = ScriptableObject.CreateInstance<CameraLocationHolder>();
        cameraLocationHolder.locations = cameraLocations;
        AssetDatabase.CreateAsset(cameraLocationHolder, "Assets/Resources/CameraLocationHolder.asset");
        AssetDatabase.SaveAssets();*/
    }

    // returns number of triangles added to model
    private int BuildMesh(MeshData mesh, List<string> doors) {
        int trisAdded = 0;
        try {
            // really big meshes crash Unity. Throw them out.
            const int maxAllowableVertices = 64000;
            const int maxAllowableIndices = maxAllowableVertices * 3;
            int tris = 0;
            foreach (SubmeshData submesh in mesh.submeshes) {
                tris += submesh.tris.Count;
            }
            if (mesh.verts.Count >= maxAllowableVertices |
               tris >= maxAllowableIndices) {
                Debug.Log("Ignoring mesh" + mesh.name + " because it is too large and will crash beast");
                return 0; // without building mesh
            }
            // gather materials
            Material[] materials = new Material[mesh.submeshes.Count];
            for (int k = 0; k < mesh.submeshes.Count; k++) {
                string sMaterialPath = Materials.directory + mesh.submeshes[k].materialName + ".mat";
                materials[k] = (Material)AssetDatabase.LoadAssetAtPath(sMaterialPath, typeof(Material));
                if (materials[k] == null) {
                    Debug.LogWarning("unable to get material " + mesh.submeshes[k].materialName + ". using default instead");
                    materials[k] = Materials.GenerateDefaultMaterial();
                }
            }
            // create mesh
            Mesh m = new Mesh();
            m.name = mesh.name;
            m.vertices = Scale(mesh.verts.ToArray());
            m.subMeshCount = mesh.submeshes.Count;
            for (int j = 0; j < mesh.submeshes.Count; j++) {
                m.SetTriangles(mesh.submeshes[j].tris.ToArray(), j);
                trisAdded += mesh.submeshes[j].tris.Count / 3;
            }
            m.RecalculateBounds();
            m.RecalculateNormals();
            m.uv = mesh.uvVerts.ToArray();
            //m.uv2 = mesh.uv2Verts.ToArray();
            m.Optimize();
            Unwrapping.GenerateSecondaryUVSet(m);
            // rotate materials
            for (int iSubmesh = 0; iSubmesh < m.subMeshCount; iSubmesh++) {
                m.uv = RotateUVs(m.uv, materials[iSubmesh].GetFloat("_Rotation"));
            }
            // add mesh to gameobject
            GameObject gO = new GameObject(mesh.name);
            gO.AddComponent<MeshFilter>();
            gO.GetComponent<MeshFilter>().sharedMesh = m;
            gO.AddComponent<MeshRenderer>();
            gO.GetComponent<MeshRenderer>().materials = materials;
            // see if the name of any door contains the name of this element
            bool isDoor = false;
            foreach (string door in doors) {
                if (mesh.name.Contains(door)) { isDoor = true; break; }
            }
            if (!isDoor) { // add collider
                gO.AddComponent<MeshCollider>();
                gO.GetComponent<MeshCollider>().sharedMesh = m;
                // add additional static occlusion flags
                gO.isStatic = true;
            } else { // add door script
                     // set as static for lightmapping and batching
                GameObjectUtility.SetStaticEditorFlags(gO, StaticEditorFlags.BatchingStatic);
                GameObjectUtility.SetStaticEditorFlags(gO, StaticEditorFlags.LightmapStatic);
                gO.AddComponent<DoorScript>();
                gO.tag = "door";
                // does not cast shadows, this avoids ugly shadowning when door dissppears
                gO.GetComponent<Renderer>().shadowCastingMode = UnityEngine.Rendering.ShadowCastingMode.Off;
            }
            return trisAdded;
        } catch (Exception e) {
            Debug.LogWarning("unable to create a mesh. exeption: " + e.Message);
            // no need to rethrow, just move on to the next mesh
            return 0;
        }
    }

    private void BuildLight(LightData lightData) {

        // create equivelant light in scene
        GameObject goLight = new GameObject("light");
        goLight.tag = "light";
        goLight.AddComponent<Light>();
        Color goColor = new Color((float)(lightData.color.r),
                                  (float)(lightData.color.g),
                                  (float)(lightData.color.b));
        goLight.GetComponent<Light>().color = goColor;
        goLight.GetComponent<Light>().range = 10;
        // we must convert candelas to approximately equivelant game engine intensity
        // coeffecient determined by visual comparisons between mental ray rendering and interactive rendering
        float gameEngineIntensity = (float)(0.0008 * (float)lightData.intensity);
        goLight.GetComponent<Light>().intensity = gameEngineIntensity;
        // instantiate light at correct position
        Vector3 lightPos = new Vector3(Scale((float)lightData.xPosition),
                                       Scale((float)lightData.yPosition),
                                       Scale((float)lightData.zPosition));
        goLight.transform.Translate(lightPos, Space.World);
        goLight.gameObject.isStatic = true;
        goLight.GetComponent<Light>().shadows = LightShadows.Hard;
        // set baked only property
        // code from Unity Support, property not exposed by api
        SerializedObject serializedLightObj = new SerializedObject(goLight.GetComponent<Light>());
        SerializedProperty lightmapProp = serializedLightObj.FindProperty("m_Lightmapping");
        lightmapProp.intValue = 2; // 0 is RealtimeOnle, 1 is Auto, 2 is BakedOnly
        serializedLightObj.ApplyModifiedProperties();

    }

    private void BuildMaterial(MaterialData matData) {
        log.Write("generating " + matData.name);
        // Determining Shaders from material properties
        //                           Color | TextureMap | Transparent | Reflective
        // Transparent Reflective -----x-------------------------x----------x------
        // Transparent Colored --------x-------------------------x-----------------
        // Diffuse Textured ----------------------x--------------------------------
        // Diffuse Colored ------------x-------------------------------------------
        // Default ----------------------------------------------------------------
        //
        // a physical parrallel of our process: Given a childs block of unknown shape, we try to push it though
        // increasingly generic holes. So we would try the Small 10 pointed star hole (transparenty specular) before the
        // large round hole (simple diffuse color).  We push it through (use the shader of) the first hole it will fit.
        // The chart above is sorted from most specialized on top, to most generic on bottom. This is the order we will
        // use to test shaders.
        // Our job here is to create a Unity Material for the material handed from us.
        // the 2 is appended to AliDocument is because "AliDocument" is the namespace name.

        Material mat = null;
        mat = (Material)AssetDatabase.LoadAssetAtPath("Assets/Materials/" + matData.name + ".mat", typeof(Material));
        if (mat != null) { // we found it!
            return;
        } else
            mat = Materials.GenerateTransparentReflective(matData);
        if (mat == null)
            mat = Materials.GenerateTransparentColored(matData);
        if (mat == null)
            mat = Materials.GenerateDiffuseTextured(matData);
        if (mat == null)
            mat = Materials.GenerateDiffuseColored(matData);
        if (mat == null)
            mat = Materials.GenerateDefaultMaterial();
        // Get material Name
        string name = matData.name;
        //TODO remove invalid characters
        AssetDatabase.CreateAsset(mat, "Assets/Materials/" + name + ".mat");
    }

    static void PlaceSun() {
        try {
            // get geographic location, date and time
            string[] projectInfo = File.ReadAllLines(infoFilePath);
            // set reasonable defaults
            double latitude = 42.355167; // degrees
            double longitude = -71.126737; // degrees. 
            DateTime dateTime = new DateTime(2011, 3, 2, 17, 0, 0, System.DateTimeKind.Utc); // noon on fall equinox
            try {
                if (projectInfo[0] == "1.4") {
                    latitude = Convert.ToDouble(projectInfo[4]) * 180 / Math.PI;
                    longitude = Convert.ToDouble(projectInfo[5]) * 180 / Math.PI;
                    DateTimeKind kind = projectInfo[6] == "Utc" ? kind = DateTimeKind.Utc : kind = DateTimeKind.Local;
                    dateTime = new DateTime((long)Convert.ToDouble(projectInfo[7]), kind);
                }
            } catch (Exception) {/*swallow*/}
            double azimuth, altitude;
            GetSolarPosition(dateTime, latitude, longitude, out azimuth, out altitude);
            GameObject goLight = new GameObject("sun");
            goLight.tag = "light";
            goLight.AddComponent<Light>();
            goLight.GetComponent<Light>().type = LightType.Directional;
            goLight.GetComponent<Light>().color = new Color(0.86f, 0.93f, 1f, 1f);
            goLight.GetComponent<Light>().intensity = .6f;
            // Instantiate light at correct position
            Vector3 lightPos = new Vector3(0f, 30f, 0f);
            goLight.transform.Translate(lightPos, Space.Self);
            goLight.transform.Rotate(0, (float)azimuth, 0, Space.World); // set azimuth first
            goLight.transform.Rotate((float)altitude, 0, 0, Space.Self); // then set altitude
            goLight.gameObject.isStatic = true;
            goLight.GetComponent<Light>().shadows = LightShadows.Hard;
        } catch (Exception) {
            /*swallow*/
        }
    }

    private void SetPlayerSettings() {
        PlayerSettings.companyName = "Earlybird Technology Inc";
        PlayerSettings.productName = "Stadia";
        PlayerSettings.defaultScreenWidth = 1024;
        PlayerSettings.defaultScreenHeight = 768;
        PlayerSettings.displayResolutionDialog = ResolutionDialogSetting.HiddenByDefault;
        PlayerSettings.defaultIsFullScreen = true;
        PlayerSettings.runInBackground = false;
        PlayerSettings.captureSingleScreen = true;
        PlayerSettings.SetAspectRatio(AspectRatio.Aspect16by10, true);
        PlayerSettings.SetAspectRatio(AspectRatio.Aspect16by9, true);
        PlayerSettings.SetAspectRatio(AspectRatio.Aspect4by3, true);
        PlayerSettings.SetAspectRatio(AspectRatio.Aspect5by4, true);
        PlayerSettings.SetAspectRatio(AspectRatio.AspectOthers, true);
    }

    // --------------- Utility Functions ------------------------------------------

    private static Vector2[] RotateUVs(Vector2[] uvs, float rotationDegrees) {
        if (rotationDegrees == 0) return uvs;
        // we wish to rotate each uv point about the origin.
        Vector2[] newUVs = new Vector2[uvs.Length];
        double rotationRad = rotationDegrees * Math.PI / 180.0;
        for (int i = 0; i < uvs.Length; i++) {
            newUVs[i] = new Vector2((float)(uvs[i].x * Math.Cos(rotationRad) - uvs[i].y * Math.Sin(rotationRad)),
                                    (float)(uvs[i].x * Math.Sin(rotationRad) + uvs[i].y * Math.Cos(rotationRad)));
        }
        return newUVs;
    }
    private static void WriteFile(byte[] data, string path) {
        if (File.Exists(path)) {
            Debug.LogWarning("Unable to create " + path + " file already exists at path");
            return;
        }
        FileStream fs = new FileStream(path, FileMode.CreateNew);
        // Create the writer for data
        BinaryWriter w = new BinaryWriter(fs);
        // Write data to path
        for (int i = 0; i < data.Length; i++) {
            w.Write(data[i]);
        }
        w.Close();
        fs.Close();
    }
    static int[] getSubmeshTris(int[] submeshFaces, int[] meshTris) {
        // A listing of faces is given to us.
        // Unity knows a list of triangles that is always exactly
        // three times longer than our list of faces. Unity also
        // demands that the list of tris we give to SetTriangles()
        // is a multiple of 3.
        // Faces are related to triangles such that
        //    submeshFace[i] corresponds to meshTri[3i], meshTri[3i+1] and meshTri[3i+2]
        // Create new submeshTris array 3 times longer than the faces array
        int[] submeshTris = new int[submeshFaces.Length * 3];
        // For each face, copy corresponding meshTris to submeshTris
        for (int i = 0; i < submeshFaces.Length; i++) {
            submeshTris[3 * i] = meshTris[submeshFaces[i] * 3];
            submeshTris[3 * i + 1] = meshTris[submeshFaces[i] * 3 + 1];
            submeshTris[3 * i + 2] = meshTris[submeshFaces[i] * 3 + 2];
        }
        return submeshTris;
    }
    static UnityEngine.Vector4[] calculateTangents(UnityEngine.Mesh mesh) {
        int triangleCount = mesh.triangles.Length / 3;
        int vertexCount = mesh.vertices.Length;

        Vector3[] tan1 = new Vector3[vertexCount];
        Vector3[] tan2 = new Vector3[vertexCount];

        Vector4[] tangents = new Vector4[vertexCount];

        for (long a = 0; a < triangleCount; a += 3) {
            long i1 = mesh.triangles[a + 0];
            long i2 = mesh.triangles[a + 1];
            long i3 = mesh.triangles[a + 2];

            Vector3 v1 = mesh.vertices[i1];
            Vector3 v2 = mesh.vertices[i2];
            Vector3 v3 = mesh.vertices[i3];

            Vector2 w1 = mesh.uv[i1];
            Vector2 w2 = mesh.uv[i2];
            Vector2 w3 = mesh.uv[i3];

            float x1 = v2.x - v1.x;
            float x2 = v3.x - v1.x;
            float y1 = v2.y - v1.y;
            float y2 = v3.y - v1.y;
            float z1 = v2.z - v1.z;
            float z2 = v3.z - v1.z;

            float s1 = w2.x - w1.x;
            float s2 = w3.x - w1.x;
            float t1 = w2.y - w1.y;
            float t2 = w3.y - w1.y;

            float r = 1.0f / (s1 * t2 - s2 * t1);

            Vector3 sdir = new Vector3((t2 * x1 - t1 * x2) * r, (t2 * y1 - t1 * y2) * r, (t2 * z1 - t1 * z2) * r);
            Vector3 tdir = new Vector3((s1 * x2 - s2 * x1) * r, (s1 * y2 - s2 * y1) * r, (s1 * z2 - s2 * z1) * r);

            tan1[i1] += sdir;
            tan1[i2] += sdir;
            tan1[i3] += sdir;

            tan2[i1] += tdir;
            tan2[i2] += tdir;
            tan2[i3] += tdir;
        }


        for (long a = 0; a < vertexCount; ++a) {
            Vector3 n = mesh.normals[a];
            Vector3 t = tan1[a];

            Vector3 tmp = (t - n * Vector3.Dot(n, t)).normalized;
            tangents[a] = new Vector4(tmp.x, tmp.y, tmp.z);

            tangents[a].w = (Vector3.Dot(Vector3.Cross(n, t), tan2[a]) < 0.0f) ? -1.0f : 1.0f;
        }

        return tangents;
    }
    static UnityEngine.Vector2[] normalizeToRange0_1(UnityEngine.Vector2[] vectors) {
        // We will normalize each axis independently
        float[] x = new float[vectors.Length];
        float[] y = new float[vectors.Length];
        for (int i = 0; i < vectors.Length; i++) {
            x[i] = vectors[i].x;
            y[i] = vectors[i].y;
        }
        x = normalizeToRange0_1(x);
        y = normalizeToRange0_1(y);
        // Reassemble before returning
        for (int i = 0; i < vectors.Length; i++) {
            vectors[i].x = x[i];
            vectors[i].y = y[i];
        }
        return vectors;
    }
    static float[] normalizeToRange0_1(float[] numbers) {
        // Find the minimum and maximum of this array
        float lowestNumber = numbers[0];
        float highestNumber = numbers[0];
        for (int i = 0; i < numbers.Length; i++) {
            if (numbers[i] < lowestNumber)
                lowestNumber = numbers[i];
            if (numbers[i] > highestNumber)
                highestNumber = numbers[i];
        }
        // Shift the array so that lowestNumber is 0
        float shift = -lowestNumber;
        for (int i = 0; i < numbers.Length; i++) {
            numbers[i] += shift;
        }
        // Scale the numbers so that highestNumber is 1
        float scale = 1 / (highestNumber + shift);
        for (int i = 0; i < numbers.Length; i++) {
            numbers[i] = numbers[i] * scale;
            if (numbers[i] > 1) {
                numbers[i] = 1; // Never trust floating point operations
            }
        }
        return numbers;
    }
    static UnityEngine.Vector2[] calculateUVs(UnityEngine.Mesh mesh) {
        Vector2[] uvs = new Vector2[mesh.vertices.Length];
        int c = 0;
        while (c < uvs.Length) {
            uvs[c] = new Vector2(mesh.vertices[c].x, mesh.vertices[c].z);
            c++;
        }
        return uvs;
    }
    static UnityEngine.Quaternion EulerAnglesToQuaternion(double heading, double attitude, double bank) {
        double c1 = Math.Cos(heading / 2);
        double s1 = Math.Sin(heading / 2);
        double c2 = Math.Cos(attitude / 2);
        double s2 = Math.Sin(attitude / 2);
        double c3 = Math.Cos(bank / 2);
        double s3 = Math.Sin(bank / 2);
        double c1c2 = c1 * c2;
        double s1s2 = s1 * s2;
        float w = (float)(c1c2 * c3 - s1s2 * s3);
        float x = (float)(c1c2 * s3 + s1s2 * c3);
        float y = (float)(s1 * c2 * c3 + c1 * s2 * s3);
        float z = (float)(c1 * s2 * c3 - s1 * c2 * s3);
        return new UnityEngine.Quaternion(x, y, z, w);
    }
    static Vector3[] Scale(Vector3[] ft) {
        for (int i = 0; i < ft.Length; i++) {
            ft[i].x = Scale(ft[i].x);
            ft[i].y = Scale(ft[i].y);
            ft[i].z = Scale(ft[i].z);
        }
        return ft;
    }
    static float Scale(float ft) {
        // Ali units are cm
        // Unity units are m
        const float Coefficient = .01f;//.3048f;
        return ft * Coefficient;
    }

    // solar calculation utility functions
    // uses the date to set the "out" parameters to the ascension and declination of the sun in degrees.
    private static void GetSolarPosition(DateTime Date, double Latitude, double LongitudeInDegrees, out double AzimuthOut, out double AltitudeOut) {
        double EarthMeanRadius = 6371.01;
        double AstronomicalUnit = 149597890;
        double JulianDate = GregorianToJulian(Date);
        double DateOffset = GregorianToJulian(new DateTime(2000, 1, 1, 12, 0, 0));
        double JulianElapsedDays = JulianDate - DateOffset; //outside function

        //start function
        double RightAscensionInRadians;
        double DeclinationInRadians;
        GetRightAscensionAndDeclination(JulianElapsedDays, out RightAscensionInRadians, out DeclinationInRadians);

        Console.Out.WriteLine("RightAscension = " + RadiansToDegrees(RightAscensionInRadians));
        Console.Out.WriteLine("Declination = " + RadiansToDegrees(DeclinationInRadians));

        double LocalMeanSiderealTimeInRadians = GetLocalMeanSiderealTime(RightAscensionInRadians, DeclinationInRadians, LongitudeInDegrees, JulianElapsedDays);

        double HourAngle = LocalMeanSiderealTimeInRadians - RightAscensionInRadians;

        if (HourAngle < 0) {
            HourAngle += 2 * Math.PI;
        }
        Console.Out.WriteLine("Hour angle in degrees = " + RadiansToDegrees(HourAngle));
        double ZenithDistance = Math.Acos(Math.Cos(DegreesToRadians(Latitude)) * Math.Cos(HourAngle) * Math.Cos(DeclinationInRadians) + Math.Sin(DeclinationInRadians) * Math.Sin(DegreesToRadians(Latitude)));
        double y = -Math.Sin(HourAngle);
        double x = Math.Tan(DeclinationInRadians) * Math.Cos(DegreesToRadians(Latitude)) - Math.Sin(DegreesToRadians(Latitude)) * Math.Cos(HourAngle);
        double AzimuthInRadians = Math.Atan2(y, x);
        if (AzimuthInRadians < 0) {
            AzimuthInRadians += 2 * Math.PI;
        }
        double AzimuthInDegrees = RadiansToDegrees(AzimuthInRadians);
        Console.Out.WriteLine("AzimuthInDegrees = " + AzimuthInDegrees);
        double Parallax = (EarthMeanRadius / AstronomicalUnit) * Math.Sin(ZenithDistance);
        ZenithDistance += Parallax;
        Console.Out.WriteLine("ZenithDistance in Degrees = " + RadiansToDegrees(ZenithDistance));
        double AltitudeInRadians = 0.5 * Math.PI - ZenithDistance;
        double AltitudeInDegrees = RadiansToDegrees(AltitudeInRadians);
        Console.Out.WriteLine("Altitude in Degrees = " + AltitudeInDegrees);
        AzimuthOut = AzimuthInDegrees;
        AltitudeOut = AltitudeInDegrees;
        return;

    }

    //returns Right Ascension and Declination of the Sun on the given day in radians
    private static void GetRightAscensionAndDeclination(double JulianElapsedDays, out double RightAscension, out double Declination) {
        double Omega = 2.1429 - 0.0010394594 * JulianElapsedDays;
        double MeanLongitude = 4.895063 + 0.017202791698 * JulianElapsedDays;
        double MeanAnomaly = 6.24006 + 0.0172019699 * JulianElapsedDays;
        double EclipticLongitude = MeanLongitude + 0.03341607 * Math.Sin(MeanAnomaly) + 0.00034894 * Math.Sin(2 * MeanAnomaly) -
        0.0001134 - 0.0000203 * Math.Sin(Omega);
        double EclipticObliquity = 0.4090928 - 6.214e-9 * JulianElapsedDays + 0.0000396 * Math.Cos(Omega);
        double y = Math.Cos(EclipticObliquity) * Math.Sin(EclipticLongitude);
        double x = Math.Cos(EclipticLongitude);
        double RightAscensionInRadians = Math.Atan2(y, x);
        if (RightAscensionInRadians < 0) {
            RightAscensionInRadians += 2 * Math.PI;
        }
        double DeclinationInRadians = Math.Asin(Math.Sin(EclipticObliquity) * Math.Sin(EclipticLongitude));

        Declination = DeclinationInRadians;
        RightAscension = RightAscensionInRadians;
        return;
    }

    //returns local mean sidereal time in radians.
    private static double GetLocalMeanSiderealTime(double RightAscensionInRadians, double DeclinationInRadians, double LongitudeInDegrees, double JulianElapsedDays) {
        double GreenwichMeanSiderealTimeInHours = ConvertJulianDateToGreenwichMeanSiderealTime(JulianElapsedDays);
        double GreenwichMeanSiderealTimeInDegrees = GreenwichMeanSiderealTimeInHours * 15;
        Console.Out.WriteLine("GMST = " + GreenwichMeanSiderealTimeInHours);
        double LocalMeanSiderealTimeInDegrees = (GreenwichMeanSiderealTimeInDegrees + LongitudeInDegrees) % 360;
        if (LocalMeanSiderealTimeInDegrees < 0) {
            LocalMeanSiderealTimeInDegrees += 360;
        }
        double LocalMeanSiderealTimeInRadians = DegreesToRadians(LocalMeanSiderealTimeInDegrees);
        return LocalMeanSiderealTimeInRadians;
    }

    private static double GregorianToJulian(DateTime Date) {
        return Date.ToOADate() + 2415018.5;
    }
    private static double RadiansToDegrees(double Radians) {
        return Radians * (180 / Math.PI);
    }
    private static double DegreesToRadians(double Degrees) {
        return (Math.PI / 180) * Degrees;
    }
    private static double ConvertJulianDateToGreenwichMeanSiderealTime(double JulianDate) {
        return (18.697374558 + 24.06570982441908 * JulianDate) % 24;
    }
}
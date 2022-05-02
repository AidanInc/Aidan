using System.Collections.Generic;

public class MeshData {
	public MeshData() {
		verts = new List<Vector3>();
		uvVerts = new List<Vector2>();
		uv2Verts = new List<Vector2>();
		submeshes = new List<SubmeshData>();
		name = "";
	}
	public string name;
	public List<Vector3> verts;
	public List<Vector2> uvVerts;
	public List<Vector2> uv2Verts;
	public List<SubmeshData> submeshes;
}

public class SubmeshData
{
	public SubmeshData()
	{
		materialName = "";
		tris = new List<int>();
	}
	public string materialName;
	public List<int> tris;

}
	

	public class MaterialData {
	public MaterialData() {
		name = "";
		isTransparent = false;
		mainColor = null;
		textureMap = null;
		bumpMap = null;
		normalMap = null;
	}
	public string name;
	public bool isTransparent; // if true, mainColor alpha is opacity
	public double reflectivity; // 0 is matte, 1 is fully reflective
	public ColorData mainColor;
	public MapData textureMap;
	public MapData bumpMap;
	public MapData normalMap;
}

public class ColorData {
	public ColorData() {
		r = 0;
		g = 0;
		b = 0;
		a = 0;
	}
	public double r;
	public double g;
	public double b;
	public double a;
}

public class MapData {
	public MapData() {
		xTiling = 0;
		yTiling = 0;
		extension = "";
		data = new List<byte>();
	}
	public double xTiling;
	public double yTiling;
	public double rotation;
	public string extension;
	public List<byte> data;
}

public class LightData {
	public LightData() {
		xPosition = 0;
		yPosition = 0;
		zPosition = 0;
		intensity = 0;
		color = new ColorData();
	}
	public double xPosition;
	public double yPosition;
	public double zPosition;
	public double intensity;
	public ColorData color;
}

public class CameraData {
	public CameraData() {
		name = "";
		xPosition = 0;
		yPosition = 0;
		zPosition = 0;
		xRotation = 0;
		yRotation = 0;
		zRotation = 0;
	}
	public string name;
	public double xPosition;
	public double yPosition;
	public double zPosition;
	public double xRotation; // gimball lock is not an issue here
	public double yRotation; // because unity will convert rotation
	public double zRotation; // to quaternion for runtime. boom.
}

public class Vector2 {
	float x;
	float y;
	public Vector2(float X, float Y) {
		x = X;
		y = Y;
	}

	// added ovride tostring function
	public override string ToString()
	{

		return " X:" + x + " Y:" + y ;
	}
}

public class Vector3 {
	float x;
	float y;
	float z;
	public Vector3(float X, float Y, float Z) {
		x = X;
		y = Y;
		z = Z;
	}
		
	public override string ToString() {

		return " X:" + x + " Y:"+ y  + " Z:"+ z  ;
	}

}
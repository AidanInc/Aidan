using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

public class Reader
{
	//private MemoryStream storeStream;
	private BinaryReader r;
	private const char MATERIAL = (char)1;
	private const char LIGHT = (char)2;
	private const char MESH = (char)4;

	private System.Text.Encoding enc = new System.Text.ASCIIEncoding();

	// constructor
	public Reader(string path)
	{
		try
		{
			// open file stream
			FileStream inStream = File.OpenRead(path);
			r = new BinaryReader(inStream);
		}
		catch (Exception e)
		{
			throw e;
		}
	}

	public bool NextElementIsMaterial()
	{
		// PeekChar doesn't advance reader position
		int next = r.PeekChar();
		return (next == MATERIAL);
	}
	public bool NextElementIsLight()
	{
		int next = r.PeekChar();
		return (next == LIGHT);
	}

	public bool NextElementIsMesh()
	{
		int next = r.PeekChar();
		return (next == MESH);
	}

	public MeshData NextMesh()
	{
		try
		{
			MeshData meshData = new MeshData();
			if (r.ReadByte() != MESH) throw new IOException("can not read mesh");
			int nameSize = r.ReadInt32();

			meshData.name = enc.GetString(r.ReadBytes(nameSize));
			int numVerts = r.ReadInt32();
			for (int i = 0; i < numVerts; i++)
			{
				meshData.verts.Add(new Vector3((float)r.ReadDouble(),     // x
											   (float)r.ReadDouble(),     // y
											   (float)r.ReadDouble()));   // z
				meshData.uvVerts.Add(new Vector2((float)r.ReadDouble(),   // u
												 (float)r.ReadDouble())); // v
																		  // meshData.uv2Verts.Add(new Vector2((float)r.ReadDouble(),  // u2
																		  //                                   (float)r.ReadDouble()));// v2
			}
			meshData.verts.TrimExcess();
			meshData.uvVerts.TrimExcess();

			int numSubmeshes = r.ReadInt32();
			for (int i = 0; i < numSubmeshes; i++)
			{
				SubmeshData submeshData = new SubmeshData();
				int materialNameSize = r.ReadInt32();
				submeshData.materialName = enc.GetString(r.ReadBytes(materialNameSize));
				int numTris = r.ReadInt32();
				List<int> tempTris = new List<int>();
				for (int j = 0; j < numTris * 3; j++)
					tempTris.Add(r.ReadInt32());
				tempTris.TrimExcess();
				// reverse tris 
				// convert from v0, v1, v2, v3, v4... to v2, v1, v0, v5, v4, v3
				for (int k = 0; k < tempTris.Count; k += 3)
				{
					submeshData.tris.Add(tempTris[k + 2]);
					submeshData.tris.Add(tempTris[k + 1]);
					submeshData.tris.Add(tempTris[k]);
				}
				submeshData.tris.TrimExcess();
				meshData.submeshes.Add(submeshData);
			}
			meshData.submeshes.TrimExcess();
			return meshData;
		}
		catch (Exception e)
		{
			throw e;
		}
	}

	public LightData NextLight()
	{
		try
		{
			LightData lightData = new LightData();
			if (r.ReadByte() != LIGHT) throw new IOException("unable to read light");
			lightData.xPosition = r.ReadDouble();
			lightData.yPosition = r.ReadDouble();
			lightData.zPosition = r.ReadDouble();
			lightData.color.r = r.ReadDouble();
			lightData.color.g = r.ReadDouble();
			lightData.color.b = r.ReadDouble();
			lightData.intensity = r.ReadDouble();
			return lightData;
		}
		catch (Exception e)
		{
			throw e;
		}
	}

	public MaterialData NextMaterial()
	{
		const byte NAME = 50;
		const byte ISTRANSPARENT = 51;
		const byte MAINCOLOR = 52;
		const byte MAINTEXTURE = 53;
		//const byte BUMPMAP = 54;
		//const byte NORMALMAP = 55;
		const byte REFLECTIVITY = 56;

		try
		{
			MaterialData matData = new MaterialData();
			if (r.ReadByte() != MATERIAL) throw new IOException("unable to read material");
			int numProperties = r.ReadInt32();
			for (int i = 0; i < numProperties; i++)
			{
				byte propertyIndicator = r.ReadByte();
				switch (propertyIndicator)
				{
					case NAME:
						int stringSize = r.ReadInt32();
						matData.name = enc.GetString(r.ReadBytes(stringSize));
						break;
					case ISTRANSPARENT:
						matData.isTransparent = (r.ReadByte() != 0); // 0 is false, anything else is true
						break;
					case MAINCOLOR:
						matData.mainColor = new ColorData();
						matData.mainColor.r = r.ReadDouble();
						matData.mainColor.g = r.ReadDouble();
						matData.mainColor.b = r.ReadDouble();
						matData.mainColor.a = r.ReadDouble();
						break;
					case MAINTEXTURE:
						matData.textureMap = new MapData();
						matData.textureMap.xTiling = r.ReadDouble();
						matData.textureMap.yTiling = r.ReadDouble();
						//matData.textureMap.rotation = r.ReadDouble();
						int mainTextureExtensionSize = r.ReadInt32();
						matData.textureMap.extension = enc.GetString(r.ReadBytes(mainTextureExtensionSize));
						int mainTextureDataSize = r.ReadInt32();
						matData.textureMap.data = r.ReadBytes(mainTextureDataSize).ToList();
						break;
					case REFLECTIVITY:
						matData.reflectivity = r.ReadDouble();
						break;
				}
			}
			return matData;
		}
		catch (Exception e)
		{
			throw e;
		}
	}
}
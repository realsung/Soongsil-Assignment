import boto3
import json

def compare_faces():

    client=boto3.client('rekognition')

    image=open('3-1.jpg','rb')
    image2=open('3-2.jpg','rb')
	
    response = client.compare_faces(SourceImage={'Bytes': image.read()}, TargetImage={'Bytes': image2.read()})
    
    print('Detected faces')    
    for faceDetail in response['FaceMatches']:
        print(faceDetail)
        print(f"Similarity : {faceDetail['Similarity']}")

    return len(response['FaceMatches'])

def main():
    face_count=compare_faces()
    print("Faces compared: " + str(face_count))


if __name__ == "__main__":
    main()

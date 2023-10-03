import 'dart:io';

import 'package:cloud_firestore/cloud_firestore.dart';
import 'package:firebase_auth/firebase_auth.dart';
import 'package:firebase_storage/firebase_storage.dart';
import 'package:flutter/material.dart';
import 'package:image_picker/image_picker.dart';
import 'package:firebase_storage/firebase_storage.dart' as firebase_storage;
import 'package:path/path.dart';
import 'package:provider/provider.dart';
import 'package:shrine/main.dart';
import 'package:firebase_database/firebase_database.dart';

class AddPage extends StatefulWidget {
  const AddPage({Key? key}) : super(key: key);

  @override
  State<AddPage> createState() => _AddPageState();
}

class _AddPageState extends State<AddPage> {
  final _name = TextEditingController();
  final _price = TextEditingController();
  final _discript = TextEditingController();
  String _imageurl = "";

  firebase_storage.FirebaseStorage storage = firebase_storage.FirebaseStorage.instance;
  FirebaseFirestore db = FirebaseFirestore.instance;
  final storageRef = FirebaseStorage.instance.ref();


  File? _image;

  Future imgFromGallery() async {
    final image = await ImagePicker().pickImage(source: ImageSource.gallery);
    if(image == null) return;
    final imageTemp = File(image.path);

    setState(() {
      this._image = imageTemp;
    });
  }

  Future<String> uploadFile() async {
    if (_image == null) {
      _imageurl = 'https://handong.edu/site/handong/res/img/logo.png';
    }
    final name = _name.text;
    final destination = '/$name';

    final ref = firebase_storage.FirebaseStorage.instance
        .ref()
        .child(destination);
    await ref.putFile(_image!);

    String down = await ref.getDownloadURL();

    setState(() {
      _imageurl = down;
    });

    return down;
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Add'),
        backgroundColor: Colors.grey,
        leading: Padding(
          padding: const EdgeInsets.only(left: 10,),
          child: TextButton(
            onPressed: () {
              Navigator.pop(context);
            },
            child: const Text('Cancel', style: TextStyle(color: Colors.black, fontSize: 15,),),
          ),
        ),
        leadingWidth: 100,
        actions: <Widget>[
          Padding(
            padding: const EdgeInsets.only(right: 10,),
            child: TextButton(
              child: const Text('Save', style: TextStyle(color: Colors.white, fontSize: 15,),),
              onPressed: () async {
                uploadFile();
                String name = _name.text;
                final imageUrl = await storageRef.child(name).getDownloadURL();
                final product = <String, dynamic>{
                  "name" : _name.text,
                  "price" : _price.text,
                  "discript" : _discript.text,
                  "imageurl" : imageUrl,
                  'timestamp': DateTime.now().millisecondsSinceEpoch,
                  'userId': FirebaseAuth.instance.currentUser!.uid,
                };

                db
                    .collection("products")
                    .doc(_name.text)
                    .set(product)
                    .onError((e, _) => print("Error writing document: $e"));
                Navigator.pop(context);
              },
            ),
          ),
        ],
      ),
      body: ListView(
        children: [
          Container(
            height: 300,
            color: Colors.grey.shade300,
            child: InkWell(
              child: _image != null?
              ClipRRect(
                borderRadius: BorderRadius.circular(50),
                child: Image.file(
                  _image!,
                  width: 100,
                  height: 100,
                  fit: BoxFit.fitHeight,
                ),
              )
              :const Center(
                child: Icon(Icons.image, color: Colors.grey, size: 100,),
              ),
              onTap: (){
                imgFromGallery();
              },
            ),
          ),
          const Align(
            alignment: AlignmentDirectional.bottomEnd,
            child: Padding(
              padding: EdgeInsets.only(top: 15, right: 10,),
              child: Icon(Icons.camera_alt),
            ),
          ),
          const SizedBox(height: 20,),
          Padding(
            padding: const EdgeInsets.only(left: 30, right: 30,),
            child: TextField(
              controller: _name,
              decoration: InputDecoration(
                label: Text('Product Name', style: TextStyle(fontWeight: FontWeight.bold, color: Colors.blue.shade800),),
              ),
            ),
          ),
          Padding(
            padding: const EdgeInsets.only(left: 30, right: 30,),
            child: TextField(
              controller: _price,
              decoration: InputDecoration(
                label: Text('Price', style: TextStyle(fontWeight: FontWeight.bold, color: Colors.blue.shade800),),
              ),
            ),
          ),
          Padding(
            padding: const EdgeInsets.only(left: 30, right: 30,),
            child: TextField(
              controller: _discript,
              decoration: InputDecoration(
                label: Text('Discription', style: TextStyle(fontWeight: FontWeight.bold, color: Colors.blue.shade800),),
              ),
            ),
          ),
        ],
      ),
    );
  }
}

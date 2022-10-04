// Copyright 2018-present the Flutter authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

import 'package:flutter/material.dart';
import 'package:intl/intl.dart';
import 'package:url_launcher/url_launcher.dart';

import 'model/product.dart';
import 'model/products_repository.dart';

final Uri _url = Uri.parse('https://www.handong.edu/');


const List<Widget> togglebut = <Widget>[
  Icon(Icons.list, size: 20,),
  Icon(Icons.view_column, size: 20,),
];

class HomePage extends StatefulWidget{
  const HomePage({Key? key}) : super(key: key);

  @override
  State<StatefulWidget> createState() => _HomePage();
}

class _HomePage extends State<HomePage> {
  final List<bool> _isSelected = <bool>[false, true];
  ViewType _viewType = ViewType.grid;
  int _crossAxisCount = 2;
  double _aspectRatio = 0.88;

  List<Card> _buildGridCards(BuildContext context) {
    List<Product> products = ProductsRepository.loadProducts(Category.all);

    if (products.isEmpty) {
      return const <Card>[];
    }

    final ThemeData theme = Theme.of(context);
    final NumberFormat formatter = NumberFormat.simpleCurrency(
        locale: Localizations.localeOf(context).toString());

    return products.map((product) {
      return Card(
        clipBehavior: Clip.antiAlias,
        // TODO: Adjust card heights (103)
        child: Column(
          // TODO: Center items on the card (103)
          crossAxisAlignment: CrossAxisAlignment.start,
          children: <Widget>[
            AspectRatio(
              aspectRatio: 18 / 11,
              child: Image.asset(
                product.assetName,
                package: product.assetPackage,
                fit: BoxFit.fitWidth,
              ),
            ),
            Expanded(
              child: Padding(
                padding: const EdgeInsets.fromLTRB(16.0, 12.0, 16.0, 8.0),
                child: Column(
                  // TODO: Align labels to the bottom and center (103)
                  crossAxisAlignment: CrossAxisAlignment.start,
                  // TODO: Change innermost Column (103)
                  children: <Widget>[
                    // TODO: Handle overflowing labels (103)
                    Text(
                      product.name,
                      style: theme.textTheme.headline6,
                      maxLines: 1,
                    ),
                    const SizedBox(height: 8.0),
                    Text(
                      formatter.format(product.price),
                      style: theme.textTheme.subtitle2,
                    ),
                  ],
                ),
              ),
            ),
          ],
        ),
      );
    }).toList();
  }

  // TODO: Add a variable for Category (104)
  @override
  Widget build(BuildContext context) {
    // TODO: Return an AsymmetricView (104)
    // TODO: Pass Category variable to AsymmetricView (104)
    return Scaffold(
      appBar: AppBar(
        title: const Text("Main"),
        centerTitle: true,
        actions: <Widget>[
          IconButton(
            icon: const Icon(
              Icons.search,
              semanticLabel: 'search',
            ),
            onPressed: () {
              Navigator.pushNamed(context, '/search');
            },
          ),
          const IconButton(
            icon: Icon(
              Icons.language,
              semanticLabel: 'filter',
            ),
            onPressed: _launchUrl,
            /*pod error
            * sudo gem install cocoapods
            * sudo gem install ffi
            * cd [project directory]
            * cd ios
            * pod install*/
          ),
        ],
      ),

      body: Column(
          children:<Widget>[
            Container(
              alignment: Alignment.topRight,
              margin: const EdgeInsets.only(top:10, right: 10),
              child:
                ToggleButtons(
                onPressed: (int index) {
                  if(index==0){
                    _crossAxisCount = 1;
                    _aspectRatio = 1;
                    _viewType = ViewType.list;
                  }
                  else{
                    _crossAxisCount = 2;
                    _aspectRatio = 0.88;
                    _viewType = ViewType.grid;
                  }
                  // Respond to button selection
                  setState(() {
                    for (int i = 0; i < _isSelected.length; i++) {
                      _isSelected[i] = i == index;
                      }
                    });


                },
                color: Colors.black.withOpacity(0.60),
                selectedColor: Colors.lightBlue,
                selectedBorderColor: Colors.lightBlue,
                fillColor: Colors.lightBlue.withOpacity(0.08),
                splashColor: Colors.lightBlue.withOpacity(0.12),
                hoverColor: Colors.lightBlue.withOpacity(0.04),
                borderRadius: BorderRadius.circular(4.0),
                isSelected: _isSelected,
                children: togglebut,

                constraints: const BoxConstraints(
                  minHeight: 40.0,
                  minWidth: 40.0,
                ),
              ),
            ),
            Expanded(
              child:
                  OrientationBuilder(
                    builder: (context, orientation) {
                    return GridView.count(
                      crossAxisCount: orientation == Orientation.portrait ? _crossAxisCount : 3,
                      padding: const EdgeInsets.all(16.0),
                      childAspectRatio: _aspectRatio,
                      children: _buildGridCards(context),
                  );
                }
              ),
            ),
          ]
      ),

      resizeToAvoidBottomInset: false,

      drawer: Drawer(
        child: ListView(
          padding: EdgeInsets.zero,
          children: [
            DrawerHeader(
              child: Stack(
                children: const [
                  Positioned(
                    bottom: 10.0,
                    left: 30.0,
                    child: Text(
                      "Pages",
                      style: TextStyle(color: Colors.white, fontSize: 28),
                    ),
                  )
                ],
              ),
              decoration: const BoxDecoration(
                color: Colors.blue,
              ),
            ),
            ListTile(
              leading: const Icon(Icons.home, color: Colors.lightBlue,),
              contentPadding: const EdgeInsets.fromLTRB(40, 5, 5, 5),
              title: const Text('Home'),
              onTap: () {
                Navigator.pushNamed(context, '/');
              },
            ),
            ListTile(
              leading: const Icon(Icons.search, color: Colors.lightBlue,),
              contentPadding: const EdgeInsets.fromLTRB(40, 5, 5, 5),
              title: const Text('Search'),
              onTap: () {
                Navigator.pushNamed(context, '/search');
              },
            ),
            ListTile(
              leading: const Icon(Icons.location_city, color: Colors.lightBlue,),
              contentPadding: const EdgeInsets.fromLTRB(40, 5, 5, 5),
              title: const Text('Favorite Hotel'),
              onTap: () {
                Navigator.pushNamed(context, '/list');
              },
            ),
            ListTile(
              leading: const Icon(Icons.person, color: Colors.lightBlue,),
              contentPadding: const EdgeInsets.fromLTRB(40, 5, 5, 5),
              title: const Text('My Page'),
              onTap: () {
                Navigator.pushNamed(context, '/go');
              },
            ),
            ListTile(
              leading: const Icon(Icons.logout, color: Colors.lightBlue,),
              contentPadding: const EdgeInsets.fromLTRB(40, 5, 5, 5),
              title: const Text('Log Out'),
              onTap: () {
                Navigator.pushNamed(context, '/login');
              },
            ),
          ],
        ),
      ),
    );
  }
}

Future<void> _launchUrl() async {
  if (!await launchUrl(_url)) {
    throw 'Could not launch $_url';
  }
}

enum ViewType { grid, list }
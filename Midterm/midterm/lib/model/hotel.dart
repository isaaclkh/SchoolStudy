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

enum Category {
  all,
  a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,
}

class Hotel {
  const Hotel({
    required this.category,
    required this.id,
    required this.name,
    required this.location,
    required this.star,
    required this.telephone,
    required this.detail,
    required this.page,
  });

  final Category category;
  final String id;
  final String name;
  final String location;
  final int star;
  final String telephone;
  final String detail;
  final String page;

  //String get assetName => '/assets/hotels/$id.jpg';
  //String get assetPackage => 'hotel_images';

  @override
  String toString() => "$name (id=$id)";
}

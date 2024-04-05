use geojson::{FeatureCollection, GeoJson};

fn main() {
    let s = include_str!("/var/home/dmytro/Downloads/all/melbourne/routes.geojson");
    let j = s.parse::<GeoJson>().unwrap();
    let f = FeatureCollection::try_from(j).unwrap();
    let f = f
        .features
        .iter()
        .filter(|f| f.property("route_type").unwrap().to_string() == "3");
    let n = f
        .map(|f| f.property("route_name").unwrap().to_string())
        .collect::<Vec<_>>();

    println!("{n:#?}");
}

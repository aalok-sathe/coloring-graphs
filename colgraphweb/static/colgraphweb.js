/* colgraphweb.js */

var options = {
    "interaction": {"hover": true},
	"manipulation": {"enabled": true},
    "configure": {"enabled": false},
    "edges": {
        "color": {"inherit": true},
        "smooth": {
            "enabled": false,
            "type": "continuous"
         }
    },
    "nodes": {
        "shape": "dot"
    },
    "interaction": {
        "hover": true,
        "dragNodes": true,
        "hideEdgesOnDrag": true,
        "hideNodesOnDrag": false
    },
    "physics": {
        "barnesHut": {
            "avoidOverlap": 0,
            "centralGravity": 0.5,
            "damping": 0.09,
            "gravitationalConstant": -80000,
            "springConstant": 0.001,
            "springLength": 250
        },
        "enabled": true,
        "stabilization": {
            "enabled": true,
            "fit": true,
            "iterations": 100,
            "onlyDynamicEdges": false,
            "updateInterval": 10
        }
    }
};

// same options for
var bgoptions = mcgoptions = cgoptions = options;

// create a basegraph
var bgcontainer = document.getElementById('bgcontainer');
var bgdata = {
    nodes: bgnodes,
    edges: bgedges
};

var basegraph = new vis.Network(bgcontainer, bgdata, bgoptions);


// create a coloringgraph
var cgcontainer = document.getElementById('cgcontainer');
var cgdata = {
    nodes: cgnodes,
    edges: cgedges
};

var coloringgraph = new vis.Network(cgcontainer, cgdata, cgoptions);


// create a metagraph
var mcgcontainer = document.getElementById('mcgcontainer');
var mcgdata = {
    nodes: mcgnodes,
    edges: mcgedges
};

var metacoloringgraph = new vis.Network(mcgcontainer, mcgdata, mcgoptions);


function objectToArray(obj) {
    return Object.keys(obj).map(function (key) {
      obj[key].id = key;
      return obj[key];
    });
}

function exportNetwork(network) {

    function addConnections(elem, index) {
        elem.connections = network.getConnectedNodes(index);
    }

    var nodes = objectToArray(network.getPositions());
    nodes.forEach(addConnections);
    // pretty print node data
    var exportValue = JSON.stringify(nodes, undefined, 2);

    return exportValue;
}

function generate(e) {
    alert('!');
    // e.preventDefault();
    var value = exportNetwork(basegraph);
    alert(value);
    $.ajax({
        type: "POST",
        url: "/",
        data: value,
        contentType: "application/json; charset=utf-8",
        dataType: "json",
        success: function (data) {
            alert(JSON.stringify(data));
        }
    });

}

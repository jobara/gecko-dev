const { actions, snapshotState: states } = require("../constants");
const { getSnapshot } = require("../utils");

let handlers = Object.create({});

handlers[actions.TAKE_SNAPSHOT_START] = function (snapshots, { snapshot }) {
  return [...snapshots, snapshot];
};

handlers[actions.TAKE_SNAPSHOT_END] = function (snapshots, action) {
  return snapshots.map(snapshot => {
    if (snapshot.id === action.snapshot.id) {
      snapshot.state = states.SAVED;
      snapshot.path = action.path;
    }
    return snapshot;
  });
};

handlers[actions.READ_SNAPSHOT_START] = function (snapshots, action) {
  let snapshot = getSnapshot(snapshots, action.snapshot);
  snapshot.state = states.READING;
  return [...snapshots];
};

handlers[actions.READ_SNAPSHOT_END] = function (snapshots, action) {
  let snapshot = getSnapshot(snapshots, action.snapshot);
  snapshot.state = states.READ;
  return [...snapshots];
};

handlers[actions.TAKE_CENSUS_START] = function (snapshots, action) {
  let snapshot = getSnapshot(snapshots, action.snapshot);
  snapshot.state = states.SAVING_CENSUS;
  snapshot.census = null;
  return [...snapshots];
};

handlers[actions.TAKE_CENSUS_END] = function (snapshots, action) {
  let snapshot = getSnapshot(snapshots, action.snapshot);
  snapshot.state = states.SAVED_CENSUS;
  snapshot.census = action.census;
  return [...snapshots];
};

handlers[actions.SELECT_SNAPSHOT] = function (snapshots, action) {
  return snapshots.map(s => {
    s.selected = s.id === action.snapshot.id;
    return s;
  });
};

module.exports = function (snapshots=[], action) {
  let handler = handlers[action.type];
  if (handler) {
    return handler(snapshots, action);
  }
  return snapshots;
};

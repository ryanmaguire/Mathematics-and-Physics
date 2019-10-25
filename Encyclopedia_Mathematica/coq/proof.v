Structure Group : Type := makeGroup
{
  A :> Set;

  op : A -> A -> A ;
  inv : A -> A ;
  z : A ;

  op_assoc : forall a b c, op a (op b c) = op (op a b) c;
  op_z : forall a, op a z = a /\ op z a = a ;
  op_inverse : forall a, op a (inv a) = z /\ op (inv a) a = z
}.

Notation "x <*> y" := (op x y) (at level 50, left associativity).

(* This lets us prove some basic stuff like left/right cancellation *)

Lemma group_cancel_l: forall (a b c : (Group : G)), a <*> b = a <*> c -> b = c.
Lemma group_cancel_r: forall (a b c :G), b <*> a = c <*> a -> b = c.

(* Left/right cancellation lets us show the identity is unique *)
Theorem id_is_unique: forall a : G, (forall b : G, a <*> b = b) -> a = z.
Proof
  intros a ADef.
  apply (group_cancel_r (inv a)).
  rewrite group_z_l; apply ADef.
Qed.